#include <ESP32Servo.h>

// Definición de pines para los 8 microservos
const int SERVO_PINS[] = {36, 39, 41, 40, 42, 38, 35, 34};
const int NUM_SERVOS = 8;

// Crear instancias de servos
Servo servos[NUM_SERVOS];

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("ESP32 - Control de 8 Microservos");
  Serial.println("========================================");
  
  // Inicializar cada servo en su pin correspondiente
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(SERVO_PINS[i], 1000, 2000);
    Serial.print("Servo ");
    Serial.print(i + 1);
    Serial.print(" inicializado en GPIO pin: ");
    Serial.println(SERVO_PINS[i]);
  }
  
  delay(2000);
  
  // Posicionar todos los servos a 90 grados (posición central)
  Serial.println("\nPosicionando todos los servos a 90°...");
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(90);
  }
  delay(2000);
  
  Serial.println("¡Sistema listo!");
  Serial.println("Iniciando secuencia de movimiento...\n");
}

void loop() {
  // Secuencia 1: Todos los servos se mueven de 0° a 180°
  Serial.println("--- Movimiento 1: Barrido 0° a 180° ---");
  for (int angulo = 0; angulo <= 180; angulo += 10) {
    for (int i = 0; i < NUM_SERVOS; i++) {
      servos[i].write(angulo);
    }
    Serial.print("Ángulo: ");
    Serial.println(angulo);
    delay(100);
  }
  
  delay(1000);
  
  // Secuencia 2: Todos los servos se mueven de 180° a 0°
  Serial.println("--- Movimiento 2: Barrido 180° a 0° ---");
  for (int angulo = 180; angulo >= 0; angulo -= 10) {
    for (int i = 0; i < NUM_SERVOS; i++) {
      servos[i].write(angulo);
    }
    Serial.print("Ángulo: ");
    Serial.println(angulo);
    delay(100);
  }
  
  delay(1000);
  
  // Secuencia 3: Movimiento secuencial (uno por uno)
  Serial.println("--- Movimiento 3: Secuencial ---");
  for (int i = 0; i < NUM_SERVOS; i++) {
    Serial.print("Moviendo Servo ");
    Serial.println(i + 1);
    
    // Mover de 0° a 180°
    for (int angulo = 0; angulo <= 180; angulo += 30) {
      servos[i].write(angulo);
      delay(50);
    }
    
    // Mover de 180° a 0°
    for (int angulo = 180; angulo >= 0; angulo -= 30) {
      servos[i].write(angulo);
      delay(50);
    }
    
    // Posición central
    servos[i].write(90);
    delay(500);
  }
  
  delay(1000);
  
  // Secuencia 4: Onda (movimiento gradual)
  Serial.println("--- Movimiento 4: Onda ---");
  for (int vuelta = 0; vuelta < 2; vuelta++) {
    for (int angulo = 0; angulo <= 180; angulo += 15) {
      for (int i = 0; i < NUM_SERVOS; i++) {
        // Crear efecto de onda con desfase
        int desfase = (angulo + (i * 22)) % 180;
        servos[i].write(desfase);
      }
      delay(75);
    }
  }
  
  // Todos a posición central
  Serial.println("--- Retornando a posición central ---");
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(90);
  }
  
  delay(2000);
  Serial.println("\nSecuencia completada. Repitiendo...\n");
}

/*
 * INSTRUCCIONES DE USO:
 * 
 * 1. Descarga e instala la librería "ESP32Servo" desde el Gestor de Librerías de Arduino IDE
 * 2. Conecta los microservos:
 *    - Pin señal -> GPIO del ESP32 (según los pines definidos)
 *    - VCC -> 5V (preferiblemente con fuente externa)
 *    - GND -> GND común (conectar GND del ESP32 con GND de la fuente)
 * 3. Carga este código en la ESP32
 * 4. Abre el Monitor Serial a 115200 baud para ver el progreso
 * 
 * RANGO DE MOVIMIENTO:
 * - 0° = Posición mínima (izquierda)
 * - 90° = Posición central
 * - 180° = Posición máxima (derecha)
 * 
 * PERSONALIZACIÓN:
 * - Cambia los delay() para ajustar velocidad de movimiento
 * - Modifica los ángulos según necesites
 * - Agrega nuevas secuencias duplicando los patrones existentes
 */
