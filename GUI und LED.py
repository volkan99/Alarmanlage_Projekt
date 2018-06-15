
import serial

from tkinter import*

Arduino_Verbindung = serial.Serial ("/dev/cu.usbmodem1411", 9600)


def an():
     Arduino_Verbindung.write(b'1')


def aus():
     Arduino_Verbindung(b'0')


Lampe_GUI = Tk()

Lampe_GUI.title ("Schalter für Lampe")

btn = Button(Lampe_GUI, text="ON", command=an)
btn1= Button(Lampe_GUI, text="OFF", command=aus)

btn.grid(row=0, column=1)
btn1.grid(row=1, column=1)

Lampe_GUI.mainloop()


