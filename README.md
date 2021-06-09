# Adame_T3
### Descripccion degeneral del funcionamiento: ###
Realizar la implementación de un programa en C para la K64 tal cada cuando
arranca el sistema muestra la siguiente secuencia:

    • Amarillo
    • Rojo
    • Morado

Después del morado se muestra el amarillo, rojo, morado y así de manera
consecutiva hasta que se presiona el SW2 para mostrar la secuencia:

    • Verde
    • Azul
    • Rojo

Después del rojo se muestra el verde, azul, rojo y así de manera consecutiva
hasta que se presiona el SW3 para mostrar la secuencia:

  • Azul
  • Blanco
  • Rojo

Después del rojo se muestra el azul, blanco, rojo y así de manera consecutiva
hasta que se presiona el SW3 para mostrar la secuencia:

  • Verde
  • Morado
  • Amarillo

Después del amarillo se muestra el verde, morado, amarillo y así de manera
consecutiva hasta que se presiona el SW2 y se muestra la secuencia original

### Restricciones ###
    1. Se tiene que hacer uso el SDK para su desarrollo.
    2. Se tiene que configurar el Pull-up interno de los pines asociados a los SW2 y SW3.
    3. Se tiene que usar las interrupciones de los GPIO asociados a los SW2 y SW3. 
    4. Para mostrar el cambio de color se tiene pasar un segundo, y este retardo tiene que generarse mediante el PIT.
    5. No se puede hacer uso del modificador extern.
    6. Se tiene que implementar con el uso de una máquina de estados
    7. Se tiene que crear un módulo especial para el manejo del led RGB, de tal suerte que contenga todas las funciones para generar los colores
