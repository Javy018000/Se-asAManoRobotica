import cv2
import face_recognition
import os

# Ruta de la carpeta que contiene las imágenes de las personas
ruta_dataset ='C:/Users/javi1/Downloads/caras'

# Listas para almacenar los encodings faciales y los nombres correspondientes
encodings_conocidos = []
nombres_conocidos = []

# Obtener la lista de archivos en la carpeta de dataset
archivos = os.listdir(ruta_dataset)

# Cargar las imágenes y extraer los encodings de las caras
for archivo in archivos:
    ruta_imagen = os.path.join(ruta_dataset, archivo)
    imagen_cargada = face_recognition.load_image_file(ruta_imagen)
    encoding = face_recognition.face_encodings(imagen_cargada)[0]
    encodings_conocidos.append(encoding)
    nombre = os.path.splitext(archivo)[0]
    nombres_conocidos.append(nombre)

# Inicializar el detector de caras de OpenCV
detector_caras = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Inicializar la captura de video desde la URL
url = 'http://192.168.43.124/live'  # Esp32 AiThinker
vid = cv2.VideoCapture(url)

while True:
    ret, frame = vid.read()  # Obtener cuadro por cuadro
    if frame is not None:

        # Convertir el cuadro a escala de grises para el detector de caras de OpenCV
        frame_gris = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detectar caras en el cuadro actual
        caras = detector_caras.detectMultiScale(frame_gris, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        # Iterar sobre las caras detectadas
        for (x, y, w, h) in caras:
            # Extraer la región de interés (ROI) de la cara
            cara_roi = frame[y:y + h, x:x + w]

            # Convertir la imagen de la cara a formato RGB (necesario para face_recognition)
            cara_rgb = cv2.cvtColor(cara_roi, cv2.COLOR_BGR2RGB)

            # Buscar encodings faciales en la cara actual
            encoding_cara = face_recognition.face_encodings(cara_rgb)

            # Comparar el encoding facial con los encodings conocidos
            nombre = "Desconocido"
            if encoding_cara:
                coincidencias = face_recognition.compare_faces(encodings_conocidos, encoding_cara[0])
                if True in coincidencias:
                    nombre = nombres_conocidos[coincidencias.index(True)]

            # Dibujar el cuadro delimitador y el nombre sobre la cara detectada
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(frame, nombre, (x + 6, y + h - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)
            
        # Mostrar el cuadro con las caras detectadas y los nombres
        cv2.imshow('Faces', frame)

        # Presionar 'q' para salir del bucle
        if cv2.waitKey(22) & 0xFF == ord('q'):
            break
    else:
        print("El servidor está fuera de línea")
        break

# Liberar los recursos
vid.release()
cv2.destroyAllWindows()
print("Video detenido")
