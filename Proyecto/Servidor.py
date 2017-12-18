from socket import *
from thread import *
from graphics import *
import time
import Tkinter
import sys

def MensajeRecibido(cadena,numJugador):
	global i
	YaExiste = 0
	for x in range(0,len(lista_casillas)):
		if lista_casillas[x] == cadena:
			YaExiste = 1
	if cadena == '1' and YaExiste == 0:
		print "Tecleaste el numero 1"
		ptCasilla1 = Point(150,150)
		if numJugador == 1:
			msgCasilla1 = Text(ptCasilla1,"X")
		else:
			msgCasilla1 = Text(ptCasilla1,"O")
		msgCasilla1.setSize(12)
		msgCasilla1.setTextColor('white')
		msgCasilla1.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '2' and YaExiste == 0: 
		print "Tecleaste el numero 2"
		ptCasilla2 = Point(250,150)
		if numJugador == 1:
			msgCasilla2 = Text(ptCasilla2,"X")
		else:
			msgCasilla2 = Text(ptCasilla2,"O")
		msgCasilla2.setSize(12)
		msgCasilla2.setTextColor('white')
		msgCasilla2.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '3' and YaExiste == 0:
		print "Tecleaste el numero 3"
		ptCasilla3 = Point(350,150)
		if numJugador == 1:
			msgCasilla3 = Text(ptCasilla3,"X")
		else:
			msgCasilla3 = Text(ptCasilla3,"O")
		msgCasilla3.setSize(12)
		msgCasilla3.setTextColor('white')
		msgCasilla3.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '4' and YaExiste == 0:
		print "Tecleaste el numero 4"
		ptCasilla4 = Point(150,250)
		if numJugador == 1:
			msgCasilla4 = Text(ptCasilla4,"X")
		else:
			msgCasilla4 = Text(ptCasilla4,"O")
		msgCasilla4.setSize(12)
		msgCasilla4.setTextColor('white')
		msgCasilla4.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '5' and YaExiste == 0:
		print "Tecleaste el numero 5"
		ptCasilla5 = Point(250,250)
		if numJugador == 1:
			msgCasilla5 = Text(ptCasilla5,"X")
		else:
			msgCasilla5 = Text(ptCasilla5,"O")
		msgCasilla5.setSize(12)
		msgCasilla5.setTextColor('white')
		msgCasilla5.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '6' and YaExiste == 0:
		print "Tecleaste el numero 6"
		ptCasilla6 = Point(350,250)
		if numJugador == 1:
			msgCasilla6 = Text(ptCasilla6,"X")
		else:
			msgCasilla6 = Text(ptCasilla6,"O")
		msgCasilla6.setSize(12)
		msgCasilla6.setTextColor('white')
		msgCasilla6.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '7' and YaExiste == 0:
		print "Tecleaste el numero 7"
		ptCasilla7 = Point(150,350)
		if numJugador == 1:
			msgCasilla7 = Text(ptCasilla7,"X")
		else:
			msgCasilla7 = Text(ptCasilla7,"O")
		msgCasilla7.setSize(12)
		msgCasilla7.setTextColor('white')
		msgCasilla7.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '8' and YaExiste == 0:
		print "Tecleaste el numero 8"
		ptCasilla8 = Point(250,350)
		if numJugador == 1:
			msgCasilla8 = Text(ptCasilla8,"X")
		else:
			msgCasilla8 = Text(ptCasilla8,"O")
		msgCasilla8.setSize(12)
		msgCasilla8.setTextColor('white')
		msgCasilla8.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	elif cadena == '9' and YaExiste == 0:
		print "Tecleaste el numero 9"
		ptCasilla9 = Point(350,350)
		if numJugador == 1:
			msgCasilla9 = Text(ptCasilla9,"X")
		else:
			msgCasilla9 = Text(ptCasilla9,"O")
		msgCasilla9.setSize(12)
		msgCasilla9.setTextColor('white')
		msgCasilla9.draw(wind)
		lista_casillas.append(cadena)
		i+=1
	else:
		if YaExiste == 1:
			print "Casilla ya seleccionada, No hagas trampa"
		else:
			print "Mensaje no aceptado"

def ligarSocket(servidor, host, port):
    while True:
        try:
            servidor.bind((host, port))
            break

        except error as e:
            print("ERROR:", e)
def VaciarCasillas():
	msgNumero1.undraw()
	msgNumero2.undraw()
	msgNumero3.undraw()
	msgNumero4.undraw()
	msgNumero5.undraw()
	msgNumero6.undraw()
	msgNumero7.undraw()
	msgNumero8.undraw()
	msgNumero9.undraw()
	msgSubIndice1.undraw()
	msgSubIndice2.undraw()

lista_casillas = []
casillas_jugador1 = []
casillas_jugador2 = []
i=0
a=0
wind=GraphWin("Gato",500,500)
wind.setBackground("Black")
ptTitle=Point(250,25)
msg=Text(ptTitle,"Juego Gato")
msg.setSize(15)
msg.setTextColor('white')
msg.draw(wind)
ptSubtitulo = Point(250,70)
msgSub=Text(ptSubtitulo,"Cada casilla es un numero en el panel telefonico")
msgSub.setSize(12)
msgSub.setTextColor('white')
msgSub.draw(wind)
#Linea horizontal 1
LineaHo1 = Line(Point(100,200),Point(400,200))
LineaHo1.setOutline('white')
LineaHo1.draw(wind)
#Linea horizontal 2
LineaHo2 = Line(Point(100,300),Point(400,300))
LineaHo2.setOutline('white')
LineaHo2.draw(wind)
#Linea vertical 1
LineaVer1 = Line(Point(200,100),Point(200,400))
LineaVer1.setOutline('white')
LineaVer1.draw(wind)
#Linea vertical 2
LineaVer2 = Line(Point(300,100),Point(300,400))
LineaVer2.setOutline('white')
LineaVer2.draw(wind)
#Numero 1
ptnumero1 = Point(150,150)
msgNumero1 = Text(ptnumero1,"1")
msgNumero1.setSize(12)
msgNumero1.setTextColor('white')
msgNumero1.draw(wind)
#Numero 2
ptnumero2 = Point(250,150)
msgNumero2 = Text(ptnumero2,"2")
msgNumero2.setSize(12)
msgNumero2.setTextColor('white')
msgNumero2.draw(wind)	
#Numero 3
ptnumero3 = Point(350,150)
msgNumero3 = Text(ptnumero3,"3")
msgNumero3.setSize(12)
msgNumero3.setTextColor('white')
msgNumero3.draw(wind)
#Numero 4
ptnumero4 = Point(150,250)
msgNumero4 = Text(ptnumero4,"4")
msgNumero4.setSize(12)
msgNumero4.setTextColor('white')
msgNumero4.draw(wind)
#Numero 5
ptnumero5 = Point(250,250)
msgNumero5 = Text(ptnumero5,"5")
msgNumero5.setSize(12)
msgNumero5.setTextColor('white')
msgNumero5.draw(wind)
#Numero 6
ptnumero6 = Point(350,250)
msgNumero6 = Text(ptnumero6,"6")
msgNumero6.setSize(12)
msgNumero6.setTextColor('white')
msgNumero6.draw(wind)
#Numero 7
ptnumero7 = Point(150,350)
msgNumero7 = Text(ptnumero7,"7")
msgNumero7.setSize(12)
msgNumero7.setTextColor('white')
msgNumero7.draw(wind)
#Numero 8
ptnumero8 = Point(250,350)
msgNumero8 = Text(ptnumero8,"8")
msgNumero8.setSize(12)
msgNumero8.setTextColor('white')
msgNumero8.draw(wind)
#Numero 9
ptnumero9 = Point(350,350)
msgNumero9 = Text(ptnumero9,"9")
msgNumero9.setSize(12)
msgNumero9.setTextColor('white')
msgNumero9.draw(wind)
#Sub Indice 1
ptSubIndice1 = Point(160,450)
msgSubIndice1=Text(ptSubIndice1,"0\nIniciar")
msgSubIndice1.setSize(12)
msgSubIndice1.setTextColor('white')
msgSubIndice1.draw(wind)
#Sub Indice 2
ptSubIndice2 = Point(350,450)
msgSubIndice2=Text(ptSubIndice2,"#\nFinalizar")
msgSubIndice2.setSize(12)
msgSubIndice2.setTextColor('white')
msgSubIndice2.draw(wind)


os.system("clear")
host = '127.0.0.1'
port = 3905
servidor = socket(AF_INET, SOCK_STREAM)
ligarSocket(servidor, host,port)
servidor.listen(1)     # Espero la conexion con c
print("\nEsperando Jugadores")
conn,addr = servidor.accept()
print "Conexion Establecida"
while True:
        global i
        reply = conn.recv(100)
        if len(lista_casillas) == 9:
        	print "Juego terminado"
        	break
        if a == 0:
        	if reply == '#':
        		print "Se ha salido del juego"
        		break
        	elif reply == '0':
        		VaciarCasillas()
        		a+=1
        	else:
        		print "Opcion no reconocida"
        else:
	        if  i%2==0:
	            print "Jugador 1:"
	            Jugador = 1
	            if reply == '#':
	            	print "Jugador 1 ha abandonado el juego la partida ha terminado"
	            	break
	            else:
	            	MensajeRecibido(reply,Jugador)
	        elif i%2!=0:
	            print "Jugador 2:"
	            Jugador = 2
	            if reply == '#':
	            	print "Jugador 2 ha abandonado el juego la partida ha terminado"
	            	break
	            else:
	            	MensajeRecibido(reply,Jugador) 