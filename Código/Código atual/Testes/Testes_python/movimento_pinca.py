import cv2
import mediapipe as mp
import serial

# Inicializar a comunicação serial com o Arduino
arduino = serial.Serial('COM9', 9600)

# Inicializar o MediaPipe
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# Configurar o vídeo
cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

# Valores iniciais
prev_distance = -1

with mp_hands.Hands(
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
) as hands:
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
        
        # Converter o frame para RGB
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # Detectar as mãos no frame
        results = hands.process(image)
        
        # Limpar o frame
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        
        # Verificar se foram detectadas mãos
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                # Obter as coordenadas do polegar e do indicador
                thumb = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]
                index = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]
                
                # Calcular a distância entre o polegar e o indicador
                distance = int(cv2.norm((thumb.x, thumb.y), (index.x, index.y)) * 100)
                
                # Enviar o valor da distância para o Arduino apenas se houver uma mudança significativa
                if distance != prev_distance:
                    arduino.write(('X' + str(distance) + '\n').encode())
                    prev_distance = distance
        
                # Desenhar as linhas e os pontos na mão
                mp_drawing.draw_landmarks(
                    image,
                    hand_landmarks,
                    mp_hands.HAND_CONNECTIONS,
                    mp_drawing.DrawingSpec(color=(0, 0, 255), thickness=2, circle_radius=4),
                    mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2))
        
        # Mostrar o frame com as anotações
        cv2.imshow('Hand Tracking', image)
        
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
