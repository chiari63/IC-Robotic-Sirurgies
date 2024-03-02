import cv2
import mediapipe as mp
import serial

# Inicialização do Mediapipe
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# Inicialização do OpenCV para captura de vídeo
cap = cv2.VideoCapture(0)

# Aumentar o tamanho da janela
cv2.namedWindow('Hands Tracking', cv2.WINDOW_NORMAL)
cv2.resizeWindow('Hands Tracking', 1000, 800)  # Definir o tamanho desejado

# Inicialização da comunicação serial
ser = serial.Serial('COM5', 9600)  # Substitua 'COM9' pela porta serial correta

# Loop principal
with mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,  # Modificado para detectar até 2 mãos
    min_detection_confidence=0.6) as hands:
    
    while cap.isOpened():
        ret, frame = cap.read()
        
        if not ret:
            print("Erro ao capturar o frame.")
            break
            
        # Conversão do frame para RGB para uso com o Mediapipe
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # Detecção das mãos
        results = hands.process(image)
        
        # Verificação do movimento das mãos e envio via porta serial
        if results.multi_hand_landmarks:
            for i, hand_landmarks in enumerate(results.multi_hand_landmarks):
                # Obtém a posição x e y do pulso
                x = hand_landmarks.landmark[mp_hands.HandLandmark.WRIST].x
                y = hand_landmarks.landmark[mp_hands.HandLandmark.WRIST].y
                
                # Mapeia os valores para o intervalo 0-255
                x_mapped = int(x * 500)
                y_mapped = int(y * 255)
                
                # Identifica qual mão com base na posição do pulso
                if x < 0.5:  # Mão esquerda
                    if i == 0:
                        ser.write(b'C' + str(x_mapped).encode() + b'\n')
                        ser.write(b'D' + str(y_mapped).encode() + b'\n')
                else:  # Mão direita
                    if i == 1:
                        ser.write(b'A' + str(x_mapped).encode() + b'\n')
                        ser.write(b'B' + str(y_mapped).encode() + b'\n')
              
        # Desenho dos pontos e linhas das mãos no frame
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(
                    image,
                    hand_landmarks,
                    mp_hands.HAND_CONNECTIONS,
                    mp_drawing.DrawingSpec(color=(0, 0, 255), thickness=2, circle_radius=4),
                    mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2))
        
        # Exibição do frame com os pontos das mãos
        cv2.imshow('Hands Tracking', image)
        
        # Condição de saída do loop
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

# Liberação dos recursos
cap.release()
cv2.destroyAllWindows()
