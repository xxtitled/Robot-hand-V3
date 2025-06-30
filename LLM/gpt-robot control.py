import io, os, time, serial
import sounddevice as sd
from pydub import AudioSegment
from openai import OpenAI

# ─── OpenAI 클라이언트 및 환경 설정 ───────────────────────────
client = OpenAI()

LLM      = os.getenv("O_LLM",      "gpt-4-1106-preview")
MAX_TOK  = int(os.getenv("O_LLM_MAX_TOKENS", 16))
TEMP     = float(os.getenv("O_LLM_TEMPERATURE", 0.4))
TTS_MOD  = os.getenv("O_TTS",      "tts-1")
VOICE    = os.getenv("O_VOICE",    "onyx")
STT_MOD  = os.getenv("O_STT",      "whisper-1")

# ─── STT (음성 → 텍스트) ────────────────────────────────────────
def record_audio(duration=2, fs=16000):
    print("[녹음] 시작…")
    data = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype="int16")
    sd.wait()
    return data.tobytes()

def transcribe(wav_bytes):
    print("[STT] 처리중…")
    res = client.audio.transcriptions.create(
        model=STT_MOD,
        file=io.BytesIO(wav_bytes),
        response_format="text"
    )
    return res

# ─── LLM (텍스트 → JSON 명령) ─────────────────────────────────
def parse_command(text: str) -> dict:
    prompt = f"""
Convert the following voice command into servo angles JSON for a 5-finger robotic hand.
Return only valid JSON, e.g. {{"thumb":90,"index":0,"middle":180,"ring":90,"pinky":0}}.
Command: "{text}"
"""
    print("[LLM] 프롬프트 전송…")
    resp = client.chat.completions.create(
        model=LLM,
        messages=[{"role":"user","content":prompt}],
        max_tokens=MAX_TOK, temperature=TEMP
    )
    return resp.choices[0].message.content  # stringified JSON

# ─── 시리얼 전송 (Arduino → 서보) ──────────────────────────────
ARDUINO_PORT = os.getenv("ARDUINO_PORT", "COM5")
BAUDRATE     = int(os.getenv("BAUDRATE", 9600))
arduino = serial.Serial(ARDUINO_PORT, BAUDRATE, timeout=1)
time.sleep(2)  # 시리얼 초기화 대기

# ─── 메인 루프 ──────────────────────────────────────────────────
if __name__ == "__main__":
    try:
        while True:
            # 1) 마이크로 음성 녹음 & STT
            wav = record_audio(duration=2)
            text = transcribe(wav)
            print("인식된 텍스트:", text)

            # 2) GPT-4o로 JSON 명령 생성
            try:
                json_cmd = parse_command(text)
                print("파싱된 JSON:", json_cmd)
            except Exception as e:
                print("LLM 파싱 에러:", e)
                continue

            # 3) Arduino에 시리얼 포맷으로 전송
            #    T###I###M###R###P###\n  (각각 3자리 정수로 고정폭)
            import json
            angles = json.loads(json_cmd)
            msg = (
                f"T{angles['thumb']:03d}"
                f"I{angles['index']:03d}"
                f"M{angles['middle']:03d}"
                f"R{angles['ring']:03d}"
                f"P{angles['pinky']:03d}\n"
            )
            arduino.write(msg.encode())
            print("[Sent]", msg.strip())

            time.sleep(0.5)

    except KeyboardInterrupt:
        print("종료 중…")
    finally:
        arduino.close()
