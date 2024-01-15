
# Robot sterowany przez ATmega328p i ESP32



## Projekt zaliczeniowy z przedmiotu "Mikrokontrolery w automatyce"

### Opis projektu

Projekt ten obejmuje stworzenie robota, który jest sterowany za pomocą mikrokontrolerów ATmega328p oraz ESP32. Robot jest zdolny do komunikacji z telefonem poprzez UART, gdzie ESP32 działa jako Access Point i serwer HTTP. Telefon łączy się z serwerem, a na utworzonej stronie znajdują się przyciski do sterowania robotem. Po wciśnięciu przycisków, ESP32 wysyła komendy poprzez UART do ATmega328p, który następnie wykonuje odpowiednie działania.

Dodatkowo, robot jest wyposażony w wyświetlacz LCD, który prezentuje aktualne parametry pracy. Sterowanie prędkością jazdy odbywa się poprzez regulację wartości wypełnienia PWM. Program na ATmega328p został napisany w całości w przerwaniach, co zapewnia efektywne działanie systemu.

### Komponenty projektu

    ATmega328p: Mikrokontroler odpowiedzialny za sterowanie ruchem robota oraz obsługę komend otrzymywanych poprzez UART.

    ESP32: Mikrokontroler pełniący rolę Access Point i serwera HTTP. Odpowiedzialny za komunikację z telefonem oraz przesyłanie komend do ATmega328p.

    Telefon: Urządzenie, które łączy się z serwerem ESP32 i umożliwia użytkownikowi sterowanie robotem poprzez interfejs internetowy.

    Wyświetlacz LCD: Moduł wykorzystywany do prezentacji aktualnych parametrów pracy robota.

    Pozostałe:
    - Potencjometr (2 szt.), przewody, płytka stykowa (2 szt.), czujnik ultradźwiękowy HC-SR04, sterownik silników DRV8335, konwerter poziomów logicznych (3v3 -> 5v), bateria 9v (2 szt.), rezystor 330 ohm, Silnik (2 szt.), koło (2 szt.), koło obrotowe, podwozie i podstawka

### Instrukcja obsługi

    Uruchomienie robota: Podłącz oba mikrokontrolery (ATmega328p i ESP32) zgodnie z instrukcją. Uruchom robot.

    Połączenie z serwerem: Na telefonie połącz się z siecią WiFi utworzoną przez ESP32. Otwórz przeglądarkę internetową i przejdź pod adres serwera (domyślnie: http://192.168.4.1).

    Sterowanie robotem: Na stronie internetowej wybierz odpowiednie przyciski do sterowania robotem. Komendy zostaną wysłane przez UART do ATmega328p.

    Monitorowanie parametrów: Obserwuj aktualne parametry pracy robota na wyświetlaczu LCD.


#### Autorzy

    Sebastian Smolik