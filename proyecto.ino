#include <DHT.h>  

#include <LiquidCrystal_I2C.h>     
LiquidCrystal_I2C lcd(0x27, 16, 2);  

int sensordht = 2;  
int led1 = 4;       
int valFotocelda = 0;
int temp, humedad;
int SensorAgua = A3;
int fuego = A2;
int beep = 6;
int valorFuego = 0;


DHT dht(sensordht, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();  
  pinMode(led1, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(beep, OUTPUT);
  pinMode(fuego, INPUT);


  //Para la pantalla LCD
  lcd.init();           //Inicializamos el LCD
  lcd.backlight();      //Activamos la luz de fondo
  lcd.clear();          //Limpiamos lo que haya en pantalla
  lcd.setCursor(0, 0);  //Iniciamos el cursor en el punto 0,0
}

void loop() {
  luminocidad();
  delay(5000);
  temperaturaHumedad();
  delay(5000);
  sensorAgua();
  delay(5000);
  sensorFuego();
  delay(5000);
}
void temperaturaHumedad() {
  humedad = dht.readHumidity();
  temp = dht.readTemperature();



  //Puerto serie
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("ºC. Humedad: ");
  Serial.print(humedad);
  Serial.println("%");

  //Para mostrarlo en el LCD
  lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
  lcd.print("Temperatura: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
  lcd.print("Humedad.  ");
  lcd.print(humedad);
  lcd.print("%");
}

void luminocidad() {
  valFotocelda = analogRead(3);
  Serial.print(valFotocelda);
  delay(160);
  if (valFotocelda < 350) {
    digitalWrite(led1, HIGH);
    lcd.setCursor(0, 0);  //Posición: columna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("Noche       ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(valFotocelda);
    lcd.print(" Intencidad");
    lcd.print("");

  } else {
    digitalWrite(led1, LOW);
    lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("Dia          ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(valFotocelda);
    lcd.print(" Intencidad");
    lcd.print("");
  }
}

void sensorAgua() {
  int agua = analogRead(SensorAgua);
  Serial.println("Sensor Agua; ");
  Serial.println(agua);
  if (agua >= 100) {
    digitalWrite(5, HIGH);
    delay(5000);
    lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("Lluvioso       ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(agua);
    lcd.print(" Agua: ");
    lcd.print("Si    ");
  } else {
    digitalWrite(5, LOW);
    delay(5000);
    lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("Seco       ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(agua);
    lcd.print(" Agua: ");
    lcd.print("No    ");
  }
  delay(1000);
}
void sensorFuego() {
  valorFuego = analogRead(fuego);
  Serial.println(valorFuego);
  if (valorFuego >= 30) {
    digitalWrite(beep, HIGH);
    delay(4000);
    digitalWrite(beep, LOW);
    delay(1000);
    lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("Fuego       ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(valorFuego);
    lcd.print(" Fuego: ");
    lcd.print("Si    ");
  } else {
    digitalWrite(beep, LOW);
      lcd.setCursor(0, 0);  //Posición: olumna 0 fila 1, para que escriba en la segunda linea
    lcd.print("Estado: ");
    lcd.print("No Fuego       ");
    lcd.setCursor(0, 1);  //Posicion: columna cero fila cero
    lcd.print(valorFuego);
    lcd.print(" Fuego: ");
    lcd.print("No    ");
  }
  delay(500);
}
