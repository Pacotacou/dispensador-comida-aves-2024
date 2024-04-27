import tensorflow as tf
from tensorflow.keras.applications.mobilenet_v2 import MobileNetV2, decode_predictions
from tensorflow.keras.preprocessing import image
import numpy as np

# Cargar el modelo preentrenado
model = MobileNetV2(weights='imagenet')

def reconocer_ave_en_imagen(ruta_imagen):
    print("reconociendo imagen")
    # Cargar la imagen
    img = image.load_img(ruta_imagen, target_size=(224, 224))
    # Preprocesar la imagen para el modelo
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    x = tf.keras.applications.mobilenet_v2.preprocess_input(x)

    # Realizar la predicción
    preds = model.predict(x)
    # Decodificar las predicciones
    results = decode_predictions(preds, top=3)[0]

    for result in results:
        if 'bird' in result[1]:
            return f"La imagen contiene un ave con una confianza del {100 * result[2]:.2f}%."
    return "La imagen no parece contener un ave."

# Prueba la función
print(reconocer_ave_en_imagen('../res/pajarillo-buscando-miel-de-las-flores.jpg'))
