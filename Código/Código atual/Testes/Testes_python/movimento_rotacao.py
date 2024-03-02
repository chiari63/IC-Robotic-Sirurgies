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
cv2.resizeWindow('Hands Tracking', 800, 600)  # Definir o tamanho desejado

# Inicialização da comunicação serial
ser = serial.Serial('COM9', 9600)  # Substitua 'COM1' pela porta serial correta

# Variáveis para armazenar as coordenadas anteriores
prev_x_thumb = 0
prev_y_thumb = 0
prev_x_middle = 0
prev_y_middle = 0

# Loop principal
with mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.5) as hands:
    
    while cap.isOpened():
        ret, frame = cap.read()
        
        if not ret:
            print("Erro ao capturar o frame.")
            break
        
        # Conversão do frame para RGB para uso com o Mediapipe
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # Detecção das mãos
        results = hands.process(image)
        
        # Verificação do movimento da mão e envio via porta serial
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                # Obtém as coordenadas do ponto na ponta do dedo polegar (polegar é 4)
                x_thumb = hand_landmarks.landmark[4].x
                y_thumb = hand_landmarks.landmark[4].y
                
                # Obtém as coordenadas do ponto na ponta do dedo médio (médio é 8)
                x_middle = hand_landmarks.landmark[8].x
                y_middle = hand_landmarks.landmark[8].y
                
                # Calcula as diferenças em relação às coordenadas anteriores (ponto no pulso)
                x_diff_thumb = x_thumb - prev_x_thumb
                y_diff_thumb = y_thumb - prev_y_thumb
                
                x_diff_middle = x_middle - prev_x_middle
                y_diff_middle = y_middle - prev_y_middle
                
                # Mapeia as diferenças para o intervalo desejado (0-255)
                x_mapped = int((x_diff_thumb * 255) + 0.5)
                y_mapped = int((y_diff_middle * 255) + 0.5)
                
                # Envia os valores via porta serial para o Arduino
                ser.write(b'X' + str(x_mapped).encode() + b'\n')  # Movimento horizontal
                ser.write(b'Y' + str(y_mapped).encode() + b'\n')  # Movimento vertical
                
                # Atualiza as coordenadas anteriores
                prev_x_thumb = x_thumb
                prev_y_thumb = y_thumb
                prev_x_middle = x_middle
                prev_y_middle = y_middle
        
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
