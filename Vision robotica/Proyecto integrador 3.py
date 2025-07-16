
import cv2
import numpy as np
def apply_filters(frame):
    filtered1 = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    filtered1[:, :, 2] = cv2.equalizeHist(filtered1[:, :, 2])
    filtered1 = cv2.cvtColor(filtered1, cv2.COLOR_HSV2BGR)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 100, 200)
    edges_color = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)

    kernel = np.ones((7, 7), np.float32) / 49
    blurred = cv2.filter2D(frame, -1, kernel)

    return filtered1, edges_color, blurred


def main():
    cap = cv2.VideoCapture(0)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

    fps = 1000
    video_writer = cv2.VideoWriter('video_con_filtros.avi', cv2.VideoWriter_fourcc(*'XVID'), fps, (1280, 960))

    start_time = cv2.getTickCount()
    while (cv2.getTickCount() - start_time) / cv2.getTickFrequency() < 5:
        ret, frame = cap.read()
        if not ret:
            break

        filtered1, edges_color, blurred = apply_filters(frame)

        cv2.imshow('Filtro 1', filtered1)
        cv2.imshow('Filtro 2', edges_color)

        combined = np.vstack((frame, blurred))
        cv2.imshow('Filtros 3 y frame original', combined)

        video_writer.write(frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    video_writer.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
