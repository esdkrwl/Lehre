Lehrveranstaltung "Internet-of-Things im schulischen Kontext"

6 M. Ed. Studis

Abschluss-Projekte:

[Smart-Mirror](https://wp.uni-oldenburg.de/internet-of-things-und-smart-home-im-schulischen-kontext-sose2019-nschneider/)

Sich morgens direkt nach dem Aufstehen beim Zähneputzen im Badezimmer bereits über die aktuellen Nachrichten, das Wetter und die Pünktlichkeit der Bahn informieren zu können, ist eine praktische Vorstellung. Ein Smart Mirror macht diese Vorstellung möglich: Ein Display wird hinter einem halbdurchlässigen Spiegel platziert, auf einem Raspberry Pi wird die nötige Software gespeichert und alles wird in einem Rahmen befestigt. 
Für dieses Projekt wurde die Software MagicMirror2 (siehe auch: https://magicmirror.builders/) verwendet, die je nach Bedarf individuell gestaltet werden kann. Es werden verschiedene Module installiert, die dann auf dem Display angezeigt werden – es gibt sowohl einige default-Module (z.B. Wettervorhersage, Uhrzeit) als auch viele 3rd-Party-Module (z.B. Bahnverbindungen). Für diesen Spiegel wurde zudem ein Bewegungsmelder installiert, der das HDMI-Signal ausschaltet, sobald eine Minute keine Bewegung vor dem Spiegel erkannt wurde und es bei Bewegung wieder einschaltet. 
Damit steht einem informativen Fertigmachen nichts mehr im Wege!


[Katzenfütterungsautomat](https://wp.uni-oldenburg.de/internet-of-things-und-smart-home-im-schulischen-kontext-sose2019-mzilles/)

Der DIY-CatFeeder ist eine über WLAN und Internet steuerbare bzw. programmierbare Fütterungsstation für Katzen (kann natürlich auch für andere Kleintiere verwendet werden). Das Rohr wird von oben mit Futter befüllt. Am unteren Ende des Rohres befindet sich ein Paddelrad, welches von dem angebrachten Motor in Bewegung gesetzt werden kann. Die Bewegung des Motors erfolgt über einen programmierten Microcontroller, welcher mit Hilfe einer Android-App gesteuert werden kann. In dieser App können zwei unabhängige Timer programmiert werden. Beide Timer können mit Hilfe der Schieberegler mit einer individuell justierbaren Futtermenge eingestellt werden. Darüber hinaus kann bei Bedarf im unteren Teil der App jederzeit sofort eine gewünschte Futtermenge herausgegeben werden.

[Smarte Bewässerung](https://wp.uni-oldenburg.de/internet-of-things-und-smart-home-im-schulischen-kontext-sose2019-mmkrtchian/)

Das Gießen einer Zimmerpflanze wird oft vernachlässigt, da andere Dinge im Alltag eine höhere Priorität aufweisen oder ein Urlaub es verhindert. Ein automatisches System zur kontrollierten Bewässerung einer Zimmerpflanze, kann somit das Gießen übernehmen.
 
Das automatische Bewässern erfolgt durch eine digitale Lösung. Automatisch wird aus einer vollen Gießkanne Wasser zur Pflanze gepumpt, sobald die Pflanze Wasser benötigt. Zusätzlich ist es möglich den Wasserstand der Pflanze mit einer App zu lesen und auch außerhalb der automatisierten Bewässerung zu gießen.
 
Die Bewässerungsanlage besteht im Wesentlichen aus einem Sensor, einer Platine mit integriertem ESP8266, einer Wasserpumpe und einer vollen Gießkanne mit Wasser.
Sowohl der Sensor, welcher die Feuchtigkeit in der Erde misst, als auch die Pumpe sind an die Platine angeschlossen. Dabei werden gemessene Spannungswerte des Sensors kontinuierlich an den ESP8266 gesendet. Ein 12V-Netzteil versorgt die Platine sowie die Pumpe mit Energie. Der ESP8266 wird mit einem Router via Wifi verbunden, um via App mit der Bewässerungsanlage kommunizieren zu können. Für die Kommunikation zwischen der Bewässerungsanlage und der App wird MQTT verwendet.
Je nach Art der Pflanze, können die Werte des Programms, welches sich auf dem ESP8266 befindet, angepasst werden. Beispielsweise benötigen Kakteen im Vergleich zu anderen Zimmerpflanzen nicht viel Wasser.
 
Der Wasserstand der Gießkanne muss manuell überprüft werden, um sicherzustellen, dass ausreichend Wasser für die Bewässerungsanlage vorhanden ist. Eine mögliche Verbesserung der Anlage wäre durch einen zusätzlichen Sensor, der den Wasserstand der Gießkanne misst und via App daran erinnert die Kanne aufzufüllen, denkbar. Da der ESP8266 nur über einen Analog-Eingang verfügt, ist entweder ein Multiplexer auf der Platine zu ergänzen oder sogar das ESP8266 mit einer anderen ESP-Version auszutauschen. 

[WiFi Personenzähler](https://wp.uni-oldenburg.de/internet-of-things-und-smart-home-im-schulischen-kontext-sose2019-hsaathoff/)

Das Projekt befasst sich mit der Einrichtung eines ESP32 als „Pax-Counter“.
Dieses Gerät nutzt die WLAN- und Bluetooth-Signale von Handys, um die Anzahl der Menschen in Reichweite des Sensors abzuschätzen.
Um die Daten nicht nur auf dem LED-Display des Mikrocontrollers anzuzeigen, wird eine Verbindung über das The Things Network, welches
auf dem LoRaWAN Standard basiert, realisiert. Somit sind die Daten auch über das Internet einsehbar. Zuletzt erfolgt eine Implementierung
des Dienstes TagIO, um eine grafische Darstellung zu ermöglichen.


[Smartes Garagentor](
https://wp.uni-oldenburg.de/internet-of-things-und-smart-home-im-schulischen-kontext-sose2019-jhanke/)

Ein Garagentor ist für viele Leute ein Gegenstand des täglichen Gebrauchs. Mehrmals am Tag wird es hoch oder runtergefahren und dabei hat man meist nicht die Fernbedienung zur Hand. Das Smartphone hingegen liegt immer griffbereit in der Tasche. Daher ist die Idee mit Hilfe eines Mikrocontrollers das Smartphone im Sinne des Internet of Things (IoT) an das Garagentor zu koppeln, um somit das Garagentor jederzeit und von überall ansteuern zu können. Zusätzlich sind Sensoren verbaut, welche den Status des Garagentors (Offen / Geschlossen) übermitteln sowie aus Sicherheitsgründen eine Lichtschranke installiert, die prüft, ob sich beim Herabfahren des Tores Gegenstände oder Personen unterhalb des Tores befinden und falls dies zutrifft den Garagentorantrieb sofort anhält und wieder hochfährt

Di., 02.04.2019, 12:00 - 14:00 Uhr 	
Seminarvorstellung

Di., 09.04.2019, 12:00 - 14:00 Uhr 	
Mikrocontroller und Funkstandards

Di., 23.04.2019, 12:00 - 14:00 Uhr 	
Elektrotechnik

Di., 30.04.2019, 12:00 - 14:00 Uhr 	
Löten

Di., 07.05.2019, 12:00 - 14:00 Uhr 	
Einstieg Mikrocontroller Programmierung

Di., 14.05.2019, 12:00 - 14:00 Uhr 	
Server Client Kommunikation

Di., 21.05.2019, 12:00 - 14:00 Uhr 	
REST	

Di., 28.05.2019, 12:00 - 14:00 Uhr 	
MQTT
Modellierung und Blynk

Di., 11.06.2019, 12:00 - 14:00 Uhr 	
Tinkern
IoT und Schule?

Di., 18.06.2019, 12:00 - 14:00 Uhr 	
Tinkern

Di., 25.06.2019, 12:00 - 14:00 Uhr 	
Tinkern

Di., 02.07.2019, 12:00 - 14:00 Uhr 	
Tinkern

Di., 09.07.2019, 12:00 - 14:00 Uhr 	
Poster Session
IoT und Schule? 