# Importar e inicializar Pygame.
from cmath import pi
import pygame
import tkinter as tk
import math
import random

pygame.init()
anchoPantalla = 800
altoPantalla = 600
tamPantalla = (800,600)

# Crear la ventana y poner el tamaño.
screen = pygame.display.set_mode(tamPantalla)

# Poner el título de la ventana.
pygame.display.set_caption("Mi Juego")

# Crear la superficie del fondo o background.
imgBackground = pygame.Surface(screen.get_size())
imgBackground = imgBackground.convert()
fondo = (255, 221, 226)
imgBackground.fill(fondo)

# Inicializar las variables de control del game loop. 
clock = pygame.time.Clock() 
salir = False
# Loop principal (game loop) del juego.
posPelota =[anchoPantalla/2, altoPantalla/2]
inicial = True
posBarraIzquierda = [40, 10]
posBarraDerecha = [anchoPantalla - 50, 10]
velocidad=[5,5]
direccionBarras = 0 #0 hacia abajo, 1 hacia arriba
direccionPelotaHorizontal = random.randrange(0, 2) #0 abajo, 1 arriba
direccionPelotaVertical = random.randrange(0, 2) #0 izquierda, 1 derecha
pixelesX = random.randrange(1, 11)
pixelesY = random.randrange(1, 11)
while not salir:

    # Timer que controla el frame rate.
    clock.tick(30)

    # Procesar los eventos que llegan a la aplicación.
    for event in pygame.event.get():
        # Si se cierra la ventana se sale del programa.
        if event.type == pygame.QUIT:
            salir = True

        # Si se pulsa la tecla [Esc] se sale del programa.
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_ESCAPE:
                salir = True
    color = (255, 131, random.randrange(131, 255, 3))
# Actualizar la pantalla.
    recta1 = pygame.Rect(70, 10, 10, altoPantalla-20)
    recta2 = pygame.Rect(anchoPantalla - 80, 10, 10, altoPantalla-20)
    barraDerecha = pygame.Rect(posBarraDerecha[0], posBarraDerecha[1], 10, 150)
    barraIzquierda = pygame.Rect(posBarraIzquierda[0], posBarraIzquierda[1], 10, 150)
    screen.blit(imgBackground, (0, 0))
    
    pygame.draw.circle(screen, color, posPelota, 50, 0)
    #creacion de las rectas divisoras
    pygame.draw.rect(screen, "#FF5C82", recta1)
    pygame.draw.rect(screen, "#FF5C82", recta2)
    #creacion de las barras en movimiento
    pygame.draw.rect(screen, color, barraDerecha)
    pygame.draw.rect(screen, color, barraIzquierda)
    
    #nueva posicion de las barras laterales
    if(posBarraIzquierda[1] <= 10):
        direccionBarras = 0
    if(posBarraIzquierda[1] >= altoPantalla - 160):
        direccionBarras = 1
    if direccionBarras == 0:
        posBarraIzquierda[1] = posBarraIzquierda[1] + 10;
        posBarraDerecha[1] = posBarraDerecha[1] + 10;
    else:
        posBarraIzquierda[1] = posBarraIzquierda[1] - 10;
        posBarraDerecha[1] = posBarraDerecha[1] - 10;
    
    #CONDICIONES A RESPETAR
    
    #Si la pelota toca el techo
    if(posPelota[1] <= 50):
            direccionPelotaVertical = 0
    #Si la pelota toca el piso
    if(posPelota[1] >= altoPantalla - 50):
            direccionPelotaVertical = 1      
    #Si la pelota toca la barra izquierda
    for x in range(150):
        distancia = math.floor(math.sqrt(((posPelota[0] - (posBarraIzquierda[0] + 10))**2)+((posPelota[1] - (posBarraIzquierda[1] + x)))**2))
        if(distancia == 50):
            direccionPelotaHorizontal = 1
    #Si la pelota toca la barra derecha
    for x in range(150):
        distancia = math.floor(math.sqrt(((posPelota[0] - (posBarraDerecha[0]))**2)+((posPelota[1] - (posBarraDerecha[1] + x))**2)))
        if(distancia == 50):
            direccionPelotaHorizontal = 0
    
    #Si la pelota pasa el limite de la barra izquierda
    distancia = posPelota[0] - 50
    if(distancia <= 30):
        inicial = True
    distancia = (anchoPantalla - 50) - posPelota[0]
    if(distancia <= 30):
        inicial = True
    
    #establece la nueva posicion de la pelota
    if inicial == True:
        posPelota = [anchoPantalla/2, altoPantalla/2]
        direccionPelotaHorizontal = random.randrange(0, 2) #0 abajo, 1 arriba
        direccionPelotaVertical = random.randrange(0, 2) #0 izquierda, 1 derecha
        inicial = False
    else:
        if direccionPelotaHorizontal == 0:
            posPelota[0] = posPelota[0] - pixelesX
        if direccionPelotaHorizontal == 1:
            posPelota[0] = posPelota[0] + pixelesX
        if direccionPelotaVertical == 0:
            posPelota[1] = posPelota[1] + pixelesY
        if direccionPelotaVertical == 1:
            posPelota[1] = posPelota[1] - pixelesY
    pygame.display.flip()
# Cerrar Pygame y liberar los recursos que pidió el programa. pygame.quit()
