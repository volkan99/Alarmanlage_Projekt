## @package Python_Code_Aufbau 
# Die graphische Benutzeroberfläche(GUI)
#
# Unser Python Code beschäftigt sich hauptsächlich mit dem Aufbau und der
# Nutzung des GUIs.
# Unser Code lässt sich grob gliedern in:
# - Bibliotheken und socket Server
# - 2 Funktionen (  aktivieren() und deaktivieren() )
# - erstellen von Buttons und Labels
# - Anordnung im GUI Fenster
#
# Die GUI beinhaltet drei Buttons:
# - online_button, der ruft beim Anklicken die aktivieren() Funktion auf
# - offline_button, dieser ruft beim draufdrücken die deaktivieren() Funktion auf
# - end_button, dieser schließt das GUI Fenster beim drauf klicken
#


from tkinter import *
import smtplib
import socket

s= socket.socket()
s.connect(( '172.20.10.2', 30303))
s.setblocking(False)

status = 0


def aktivieren():
""" Wird aufgerufen, wenn auf den "Aktivieren"-Button gedrückt wird.

Zunächst wird die Farbe des "Aktivier"-Buttons geändert, damit man erkennen
kann, dass er geklickt wurde. Dann wird der "aktiv"-Label mit Text positioniert
und es wird eine 1 versendet. Zudem werden andere Labels "unsichtbar" gemacht,
um vorherige Prozesse nicht mehr anzuzeigen. Am Ende wird die Variable auf 1 gesetzt,
damit man nur deaktivieren kann, wenn diese Variable auf 1 ist.
"""
    global status
    online_button.configure(highlightbackground="dark blue")
    aktiv_label.config(text="Anlage im alarmfähigen Zustand")
    aktiv_label.place         (x= 215, y=130, width= 250, height= 75)
    s.send(b'1')

    antwort_label.place          (x=0, y=0, width=0, height= 0)
    false_label.place            (x= 0, y=0, width=0, height= 0)

    status = 1




def deaktivieren():
    """Wird aufgerufen, wenn auf den "Deaktivieren"-Button gedrückt wird.

Es existiert ein Eingabefeld, in der man das Kennwort eingeben soll.
Wenn man nun auf den "Deaktivieren"-Button drückt und status=1 ist und
zudem das Kennwort 123 lautet, wird der "antwort"-Label mit Text positioniert,
der "false"-Label verschwindet und der "Aktivieren"-Button wird wieder zur
Ursprungsfarbe geändert. Hinzu kommt noch, dass das Eingabefeld geleert,
eine 0 versendet und status zu 0 wird.
Bei jedem anderem Kennwort werden die Labels um positioniert, die Eingabe gelöscht
und eine Email wird versendet.
Wenn jedoch status 0 ist und auf den Button geklickt wird, taucht ein Label auf,
welches einen informiert, dass die Anlage bereits inaktiv ist
"""
    global status
    kennwort = eingabefeld.get()

    if( status == 0):
        false_label.place         (x= 0, y=330, width=250, height= 30)
        antwort_label.place       (x= 0, y=0, width=0, height= 0)
        eingabefeld.delete(0,END)
        false_label.config(text="Anlage bereits inaktiv")

        
    if( status == 1):

        if ( kennwort == "123"):
            antwort_label.place       (x= 0, y=330, width=250, height= 30)
            false_label.place         (x= 0, y=0, width=0, height= 0)
            antwort_label.config(text="Eingabe erfolgreich")
        
            aktiv_label.config(text="Anlage ist deaktiviert", fg= "black")
            online_button.configure(highlightbackground="light blue")

            eingabefeld.delete(0,END)
            s.send(b'0')

            status = 0
        
        else:
            false_label.place         (x= 0, y=330, width=250, height= 30)
            antwort_label.place       (x= 0, y=0, width=0, height= 0)

            eingabefeld.delete(0,END)
            false_label.config(text="Falsche Eingabe!")

            TO = 'guerkan.yigitbas99@gmail.com'
            SUBJECT = 'Alarm!!!'
            TEXT = 'Jemand hat ein falsches Kennwort eingegeben! '
            gmail_sender = 'vorsicht.danger.vorsicht@gmail.com'
            gmail_passwd = 'Yigitbas1'
            server = smtplib.SMTP('smtp.gmail.com', 587)
            server.ehlo()
            server.starttls()
            server.login(gmail_sender, gmail_passwd)
            BODY = '\r\n'.join(['To: %s' % TO,
                    'From: %s' % gmail_sender,
                    'Subject: %s' % SUBJECT,
                    '', TEXT])

            try:
                server.sendmail(gmail_sender, [TO], BODY)

            except:
                server.quit()
        



Alarmanlage= Tk()

Alarmanlage.title ("Alarmanlage-Menü")
Alarmanlage.geometry("500x550")


online_button = Button(Alarmanlage, text= "Aktivieren", highlightbackground= "light blue", command= aktivieren)
offline_button= Button(Alarmanlage, text= "Deaktivieren", highlightbackground= "light blue", command= deaktivieren)
end_button= Button(Alarmanlage, text= "Ausschalten", highlightbackground="red", command= Alarmanlage.destroy)


anweisungs_label = Label(Alarmanlage, font= "Garamond 15 bold ", fg= "white", bg="black",
text="Folgende Funktionen stehen zur Verfügung:\nAkivieren: Stehlt die Anlage in den alarmfähigen Zustand.\nDeaktivieren: Die Anlage wird auf Stand-by geschaltet.\nAusschalten: Die Anlage wird aussgeschaltet.")
                       
info_label = Label(Alarmanlage, text= "Zum deaktivieren wird\n\
Kennwort benötigt!")
aktiv_label = Label(Alarmanlage, text= "Anlage im Alarmfähigen Zustand", fg="green")
antwort_label =Label(Alarmanlage, fg= "green")
false_label = Label(Alarmanlage, fg= "red")

eingabefeld =Entry(Alarmanlage, bd=5, width=30)
eingabefeld.insert(10,"*kennwort*")



anweisungs_label.place    (x= 0, y=10, width =500, height=100)
online_button.place       (x= 50, y=130, width=100, height=75)
offline_button.place      (x= 350, y=310, width=100, height= 75)
info_label.place          (x= 0, y=240, width=200, height= 100)
eingabefeld.place         (x= 200, y=270)
end_button.place          (x= 115, y=430, width=270, height= 75)


Alarmanlage.mainloop()
