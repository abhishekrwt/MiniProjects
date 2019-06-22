from scipy.spatial import distance as dist
from imutils.video import VideoStream, FPS
from imutils import face_utils
import imutils
import numpy as np
import time
import dlib
import cv2

def smile(mouth):
    A = dist.euclidean(mouth[3], mouth[9])
    B = dist.euclidean(mouth[2], mouth[10])
    C = dist.euclidean(mouth[4], mouth[8])
    avg = (A+B+C)/3
    D = dist.euclidean(mouth[0], mouth[6])
    mar=avg/D
    return mar

def middle(mouth):
    A = dist.euclidean(mouth[13], mouth[17])
    B = dist.euclidean(mouth[14], mouth[18])
    C = dist.euclidean(mouth[15], mouth[19])
    avg = (A+B+C)/3
    D = dist.euclidean(mouth[0], mouth[6])
    mar2=avg/D
    return mar2

COUNTER = 0
COUNTER1 = 0
TOTAL = 0

shape_predictor= "shape_predictor_68_face_landmarks.dat"
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(shape_predictor)


(mStart, mEnd) = face_utils.FACIAL_LANDMARKS_IDXS["mouth"]

print("[INFO] starting video stream thread...")
vs = VideoStream(src=0).start()
fileStream = False
time.sleep(1.0)

while True:
    frame = vs.read()
    frame = imutils.resize(frame, width=450)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)
    for rect in rects:
        shape = predictor(gray, rect)
        shape = face_utils.shape_to_np(shape)
        mouth= shape[mStart:mEnd]
        mar= smile(mouth)
        mar2=middle(mouth)
        mouthHull = cv2.convexHull(mouth)
        #print("p0",abs(mouth[0][1]-mouth[9][1]))
        #print("p6",mouth[6][1])
        #print("p3",mouth[3][1])
        #print("p9",mouth[9][1])
        cv2.drawContours(frame, [mouthHull], -1, (0, 255, 0), 1)
       

        if mar <= .26 or ((mar> .30 and mar < .37) and mar2 > .20) :
            if(abs(mouth[0][1]-mouth[9][1]) > 7):
                COUNTER += 1
                if COUNTER >= 15:
                    TOTAL += 1
                    frame = vs.read()
                    time.sleep(.3)
                    frame2= frame.copy()
                    img_name = "img/smile_{}.png".format(TOTAL)
                    cv2.imwrite(img_name, frame)
                    print("{} written!".format(img_name))
                    COUNTER = 0
        elif mar >= .40 and mar2 < .21 :
            COUNTER1 += 1
            if COUNTER1 >= 12:
                TOTAL += 1
                frame = vs.read()
                time.sleep(.3)
                frame2= frame.copy()
                img_name = "img/pout_{}.png".format(TOTAL)
                cv2.imwrite(img_name, frame)
                print("{} written!".format(img_name))
                COUNTER1 = 0

        cv2.putText(frame, "MAR: {}".format(mar), (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 255), 2)
        cv2.putText(frame, "MAR2: {}".format(mar2), (10, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (0, 0, 255), 2)
    cv2.imshow("Frame", frame)

    key2 = cv2.waitKey(1) & 0xFF
    if key2 == ord('q'):
        break

cv2.destroyAllWindows()
vs.stop()