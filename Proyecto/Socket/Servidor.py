from socket import *
from thread import *
import time
import sys

def MensajeRecibido(cadena,numCliente):
	if cadena == '1':
		print "Tecleaste el numero 1"
	elif cadena == '2':
		print "Tecleaste el numero 2"
	elif cadena == '3':
		print "Tecleaste el numero 3"
	elif cadena == '4':
		print "Tecleaste el numero 4"
	elif cadena == '5':
		print "Tecleaste el numero 5"
	elif cadena == '6':
		print "Tecleaste el numero 6"
	elif cadena == '7':
		print "Tecleaste el numero 7"
	elif cadena == '8':
		print "Tecleaste el numero 8"
	elif cadena == '9':
		print "Tecleaste el numero 9"
	else:
		print "Mensaje no aceptado"


def ligarSocket(servidor, host, port):
    while True:
        try:
            servidor.bind((host, port))
            break

        except error as e:
            print("ERROR:", e)


def recibir(conn):
    while True:
        global i
        global bandera
        reply = conn.recv(100)

        if reply[0] == '1' or i%2==0:
            print "Jugador 1:"
            Jugador = 1
            i+=1
            if reply == '#':
            	print "Jugador 1 ha abandonado el juego"
            	bandera = True
            	break
            else:
            	MensajeRecibido(reply,Jugador)
        elif reply[0] == '2' or i%2!=0:
            print "Jugador 2:"
            Jugador = 2
            i+=1
            if reply == '#':
            	print "Jugador 2 ha abandonado el juego"
            	bandera = True
            	break
            else:
            	MensajeRecibido(reply,Jugador)
        else:
        	print "No es tu turno"

def enviarEspecial(conn):
    global lista_de_clientes,client
    client = lista_de_clientes.pop()


bandera = False      # Utilizada en la desconexion/conexion de clientes

i=0

lista_de_clientes = ["2","1"]   # El servidor le asigna un numero a los
                                # clientes segun esta lista

client = ""     # Numero del cliente

def main():

    global bandera
    host = '127.0.0.1'
    port = 3900
    servidor = socket(AF_INET, SOCK_STREAM)
    ligarSocket(servidor, host,port)
    servidor.listen(2)     # Espero 2 clientes

    print("\nEsperando Jugadores")

    conn,addr = servidor.accept()
    print "Jugador 1 conectado"
    enviarEspecial(conn)               # Espero conexion del 1 cliente
    start_new_thread(recibir,(conn,))

    conn2,addr2 = servidor.accept()
    print "Jugador 2 conectado"
    enviarEspecial(conn2)              # Espero conexion del 2 cliente
    start_new_thread(recibir,(conn2,))

    while True: # Necesario para que los hilos no mueran

        if bandera != True:     # En caso de desconectarse un cliente,
                                # esperara a que otro vuelve a conectarse
            conn3,addr3 = servidor.accept()
            enviarEspecial(conn3)
            start_new_thread(recibir,(conn3,))
            bandera = False
        elif bandera == True:
        	break

main()
