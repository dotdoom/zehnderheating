Zehnder controller IRVAR 11.

For NodeMCU ESP8266.

Schematics (not really):

- connect 100-300 Ohm resistor to D2
- connect long leg of 940nm IR LED to resistor
- connect short leg of IR LED to GND

To deploy:

```shell
$ pio run -t upload
```
