import cv2 
import mediapipe as mp
import serial
import math

finger0_x = finger4_x = finger8_x = finger9_x = finger12_x = finger16_x = finger20_x = 0
finger0_y = finger4_y = finger8_y = finger9_y = finger12_y = finger16_y = finger20_y = 0

webcam = cv2.VideoCapture(0)
mp_hands = mp.solutions.hands
my_hands = mp_hands.Hands()
drawing_utils = mp.solutions.drawing_utils

arduino = serial.Serial('COM5', 9600)  # COM는 연결 시 매번 확인 후 수정
arduino.timeout = 1

while True:
    _, image = webcam.read()
    image = cv2.flip(image, 1)
    frame_height, frame_width, _ = image.shape
    rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    output = my_hands.process(rgb_image)
    hands = output.multi_hand_landmarks

    if hands:
        for hand in hands:
            drawing_utils.draw_landmarks(image, hand, mp_hands.HAND_CONNECTIONS)
            landmarks = hand.landmark
            for id, landmark in enumerate(landmarks):
                x = int(landmark.x * frame_width)
                y = int(landmark.y * frame_height)

                if id == 0:
                    finger0_x = x;  finger0_y = y
                if id == 4:
                    finger4_x = x;  finger4_y = y
                if id == 8:
                    finger8_x = x;  finger8_y = y
                if id == 9:
                    finger9_x = x;  finger9_y = y
                if id == 12:
                    finger12_x = x; finger12_y = y
                if id == 16:
                    finger16_x = x; finger16_y = y
                if id == 20:
                    finger20_x = x; finger20_y = y

        dist_1 = int(math.sqrt((finger4_x - finger9_x)**2 + (finger4_y - finger9_y)**2)) # 엄지
        dist_2 = int(math.sqrt((finger8_x - finger0_x)**2 + (finger8_y - finger0_y)**2)) # 검지
        dist_3 = int(math.sqrt((finger12_x - finger0_x)**2 + (finger12_y - finger0_y)**2)) # 중지
        dist_4 = int(math.sqrt((finger16_x - finger0_x)**2 + (finger16_y - finger0_y)**2)) # 약지
        dist_5 = int(math.sqrt((finger20_x - finger0_x)**2 + (finger20_y - finger0_y)**2)) # 소지

        cv2.putText(
            image,
            text='dist1=%d dist2=%d dist3=%d dist4=%d dist5=%d' % (dist_1, dist_2, dist_3, dist_4, dist_5),
            org=(10, 30),
            fontFace=cv2.FONT_HERSHEY_SIMPLEX,
            fontScale=0.6,
            color=(255, 0, 0),
            thickness=2
        )

        # 홀수는 '접은 상태', 짝수는 '편 상태'
        if dist_1 < 100: 
            arduino.write(b'1')
        else:
            arduino.write(b'2')

        if dist_2 < 200: 
            arduino.write(b'3')
        else:
            arduino.write(b'4')

        if dist_3 < 200:
            arduino.write(b'5')
        else:
            arduino.write(b'6')

        if dist_4 < 200:
            arduino.write(b'7')
        else:
            arduino.write(b'8')

        if dist_5 < 200:
            arduino.write(b'9')
        else:
            arduino.write(b'0')

    else:
        # 손이 카메라에 인식되어 있지 않은 상황일 때 --> 손 펴진 상태로 인식
        arduino.write(b'2')
        arduino.write(b'4')
        arduino.write(b'6')
        arduino.write(b'8')
        arduino.write(b'0')

    cv2.imshow("Img", image)
    key = cv2.waitKey(10)
    if key == 27:  # ESC key
        break

webcam.release()
cv2.destroyAllWindows()
