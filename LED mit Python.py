import serial
#test 123

arduino = serial.Serial('/dev/cu.usbmodem1411', 9600)

def An_Aus_Funktion():
    eingabe = input("Soll LED AN oder AUS sein?")

    if eingabe == AN:
        print("LED ist AN")
        arduino.write('1')

        An_Aus_Funktion()

    elif eingabe == AUS:
        print("LED ist AUS")
        arduino.write('0')

        An_Aus_Funktion()

    else:
        print("SRY. New try")

        An_Aus_Funktion()



An_Aus_Funktion()
