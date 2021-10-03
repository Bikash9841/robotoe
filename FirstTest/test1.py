

import cv2 as cv
import numpy as np
import time
import requests
import serial
import time

# for serial comunication to arduino
serialcomm = serial.Serial('/dev/ttyACM0', 57600)
serialcomm.timeout = 1

# tic-tac-toe game alogorithm uses intergers from 1-9 to locate the squares of the board
# demo board---->
#
#  1 | 2 | 3 |
#  ------------
#  4 | 5 | 6 |
# -------------
#  7 | 8 | 9 |


# Matrix to store the location of player pieces
# everytime a player places his piece into the board..newMat is updated and compared with
# prevMat to know to exact location of new piece in the board
newMat = [[0, 0, 0],
          [0, 0, 0],
          [0, 0, 0]]

prevMat = [[0, 0, 0],
           [0, 0, 0],
           [0, 0, 0]]

# these are the location of tic tac board's boxes,initial values are -1,-1 to make it 0,0 on array initialization
locX = -1
locY = -1

# give the desired coordinate of box to crop according to standard matrix
# -------(pixels(Y) go downwards but in standard matrix X go downward)
deX = 1
deY = 2

# copying newMat into prevMat


def copyMat(new, prev):
    for i in range(0, 3, 1):
        for j in range(0, 3, 1):
            prev[i][j] = new[i][j]


# counts the no. of white and black pixels
def countAndUpdateMat(img):
    whtp = np.sum(img == 255)
    blckp = np.sum(img == 0)

    if(whtp > 580):
        newMat[locY][locX] = 1

    # print('Number of white pixels:', whtp)
    # print('Number of black pixels:', blckp)


# it compares the prev and new matrix and find the location of latest piece placed in the board
def compareAndFindLoc(new, prev):
    pieceX = 0
    pieceY = 0

    # it indicates the locations of tic-tac-toe board
    boardLoc = 0
    for i in range(0, 3, 1):

        for j in range(0, 3, 1):

            if(prev[i][j] != new[i][j]):
                pieceX = i
                pieceY = j

                if(pieceX == 0 and pieceY == 0):
                    boardLoc = 1
                elif(pieceX == 0 and pieceY == 1):
                    boardLoc = 2
                elif(pieceX == 0 and pieceY == 2):
                    boardLoc = 3
                elif(pieceX == 1 and pieceY == 0):
                    boardLoc = 4
                elif(pieceX == 1 and pieceY == 1):
                    boardLoc = 5
                elif(pieceX == 1 and pieceY == 2):
                    boardLoc = 6
                elif(pieceX == 2 and pieceY == 0):
                    boardLoc = 7
                elif(pieceX == 2 and pieceY == 1):
                    boardLoc = 8
                elif(pieceX == 2 and pieceY == 2):
                    boardLoc = 9
                return boardLoc
    return boardLoc


def displayMat(new):

    for i in range(0, 3, 1):
        print('\n')
        for j in range(0, 3, 1):
            print(new[i][j], end=" ")
    print('\n')


# address of ip webcam
address = 'http://192.168.1.156:8080/shot.jpg'

# ranges of lower and higher hsv values for white chess piece
lower_range = np.array([20, 30, 135])
upper_range = np.array([35, 135, 225])

# WE manually organize the value
# of pixels in both x and y axis to crop the 9 boxes of tic tac board
# for this board----> width of each box(X)=70, height of each box(Y)=121
# ------------------>X starts from 16 and ends to 226(so that stopping value in range is 157)
# ------------------>Y starts from 0 and ends to 363(so that stopping value in range is 243)


# -----> yaah bata loop halne
while True:

    r = requests.get(address)
    img_arr = np.array(bytearray(r.content), dtype=np.uint8)
    board = cv.imdecode(img_arr, -1)
    board = cv.resize(board, (750, 750))

    # cropped so that to see only region of interest
    board = board[181:552, 157:383]

    # changed into hsv for color detection
    hsv = cv.cvtColor(board, cv.COLOR_BGR2HSV)
    board_mask = cv.inRange(hsv, lower_range, upper_range)

 # starts by copying new matrix to prev matrix
    copyMat(newMat, prevMat)

    for py in range(0, 243, 121):

        # deX follows standard matrix as LocY follows pixels coordinate which are opposite
        # this if is used to crop the desired squared box
        # if(deX == locY and deY == locX):
        #     break

        locY = locY+1

        # everytime we enter a new row we need locX to be -1 so that it will be 0 after adding 1 inside px loop
        locX = -1

        # our matrix index is upto 2 so that we did this
        if(locY >= 3):
            locY = 0

        for px in range(16, 157, 70):
            locX = locX+1

            crop = hsv[py:(py+121), px:(px+70)]

            # Filter the image and get the binary mask, where white represents
            # your target color
            mask = cv.inRange(crop, lower_range, upper_range)
            countAndUpdateMat(mask)

            # if(deX == locY and deY == locX):
            #     break

            # prints the pixel coordinates of each boxes
            # print(f'{py,(py+121)}, {px,(px+70)}')

    cv.imshow('board', board)
    # cv.imshow('board_mask', board_mask)

    boardLoc = compareAndFindLoc(newMat, prevMat)
    # displayMat(newMat)

    # send to arduino
    # while(1):
    # print(f'\n{boardLoc}')
    serialcomm.write(str(boardLoc).encode())
    # ardata = serialcomm.readline()
    # print(ardata)
    # if ardata == b'obtained\r\n':
    #     break
    while(1):
        ardata = serialcomm.readline()
        print(ardata)
        if ardata == b'nextdata\r\n':
            break

    # cv.imshow('crop', crop)
    # cv.imshow('hsv', hsv)
    time.sleep(5)
    key = cv.waitKey(1)
    if key == ord('q'):
        break

cv.destroyAllWindows()
