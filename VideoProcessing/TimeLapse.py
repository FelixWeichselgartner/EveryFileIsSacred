import cv2
import numpy as np
import sys

SHOWVIDEO = False

def frame_progess_bar():
    for i in range(30):
        sys.stdout.write('-')
    sys.stdout.write('|\n')
    sys.stdout.write('>')

def show_progress_bar(value, complete):
    width = 30
    part = complete/width
    amount = int(value/part)
    for i in range(show_progress_bar.lastAmount, amount):
        sys.stdout.write('#')
        sys.stdout.flush()
    show_progress_bar.lastAmount = amount
show_progress_bar.lastAmount = 0

def TimeLapse(filename, factor):
    # Create a VideoCapture object and read from input file
    # If the input is the camera, pass 0 instead of the video file name
    cap = cv2.VideoCapture(filename)

    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    outputFilename = 'TimeLapse_' + filename.replace('.mp4', '') + '.avi'
    print(outputFilename)
    output = cv2.VideoWriter(outputFilename, fourcc, 20.0, (1280, 720))

    count = 0

    frame_progess_bar()

    # Check if camera opened successfully
    if (not cap.isOpened()):
        print("Error opening video stream or file")

    # Read until video is completed
    while (cap.isOpened()):
        # Capture frame-by-frame
        ret, frame = cap.read()
        show_progress_bar(count, cap.get(cv2.CAP_PROP_FRAME_COUNT))

        if ret == True:
            """
            if SHOWVIDEO:
                cv2.imshow('Frame', frame)
                # Press Q on keyboard to  exit
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            """


            output.write(frame)
            count += factor
            cap.set(cv2.CAP_PROP_POS_FRAMES, count)

        # Break the loop
        else:
            break

    # When everything done, release the video capture object
    cap.release()
    output.release()

    # Closes all the frames
    cv2.destroyAllWindows()


if __name__ == "__main__":
    TimeLapse('asterix.mp4', 1000)