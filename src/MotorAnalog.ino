
// --- Bibliotecas Auxiliares ---
#include <AFMotor.h>         //Inclui biblioteca AF Motor
//CONFIGURAÇÃO
const bool ANALOGICO = true;

//codigo das direcoes
const char FRENTE = 'W';
const char TRAS = 'S';
const char ESQUERDA = 'A';
const char DIREITA = 'D';
const char PARA = 'P';

//codigo dos controles adicionais.
const char NEON = 'N';
const char BOMBA = 'B';

//porta do rele da bomba.
const int BOMBA_OUT = 13;

//codigo se o botao de direcao foi apertado ou solto.
const char APERTOU = 'P'; //seta speed
const char SOLTOU = 'E';


// --- Seleção dos Motores ---
AF_DCMotor motorL1(1); //Seleção do Motor 1 - Esquerda 1
AF_DCMotor motorL2(2); //Seleção do Motor 2 - Esquerda 2
AF_DCMotor motorR1(3); //Seleção do Motor 3 - Direita 1
AF_DCMotor motorR2(4); //Seleção do Motor 4 - Direita 1

//Abaixo as constantes e variaveis usadas pelo código.
const char VERTICAL = 0;
const char HORIZONTAL = 1;
const char NENHUMA = 'O';

char lastRead; //ULTIMA DIRECAO LIDA.
char peRead; //Le Press and Release.

bool direction[2]; //FRENTE/TRAS e ESQUERDA/DIREITA
unsigned char speed[2]; //velocidade vertical e horizontal.


void setup(){
    pinMode(BOMBA_OUT, OUTPUT);
    Serial.begin(9600);
    speed[0] = 0;
    speed[1] = 0;
    direction[0] = true;
    direction[1] = true;
}
void loop(){
    Serial.write("WAITING DIRECTION");
    while(Serial.available() <=0)
        delay(10);
    bool readed = readDirection();
    if(readed && (lastRead == FRENTE || lastRead == TRAS || lastRead == ESQUERDA || lastRead == DIREITA)){
        Serial.write("WAITING SPEED");
        while(Serial.available() <=0)
            delay(10);
        readSpeed();
        if(readed)
            calculateSpeed();
    }else if(readed){
        while(Serial.available() <=0)
            delay(10);
            controlaBombaGiro();
        }
}
void doTheLogBT(){
    while(Serial.available() > 0){
        delay(10);
        Serial.write(Serial.read());
        char lido = Serial.read();
        if(lido == 'L'){
            digitalWrite(BOMBA_OUT, HIGH);
            Serial.write("LIGOU!");
        }
        else if(lido == 'D'){
            digitalWrite(BOMBA_OUT, LOW);
            Serial.write("(des)LIGOU!");
        }
    }
}

//Le uma direcao vinda da rede.
bool readDirection(){
    // Serial.write("readDirection");
    while(Serial.available() <= 0)
        delay(10);
    if(Serial.available() > 0){
        delay(10);
        char dir = Serial.read();
        // Serial.write("\nD: ");
        // Serial.write(dir);
        // Serial.write("\n");
        lastRead = dir;
        return true;
    }
    return false;
}

//Le a velocidade para se mover naquela direcao.
void readSpeed(){
    // Serial.write("readSpeed");
    switch(lastRead){
        case FRENTE:
            speed[0] = Serial.read();
            direction[0] = true;
            // Serial.write("D: ");
            // Serial.write(speed[0]);
            // Serial.write("\n");
            return;
        case ESQUERDA:
            speed[1] = Serial.read();
            direction[1] = true;
            // Serial.write("D: ");
            // Serial.write(speed[1]);
            // Serial.write("\n");
            return;
        case TRAS:
            speed[0] = Serial.read();
            direction[0] = false;
            // Serial.write("D: ");
            // Serial.write(speed[0]);
            // Serial.write("\n");
            return;
        case DIREITA:
            speed[1] = Serial.read();
            direction[1] = false;
            // Serial.write("D: ");
            // Serial.write(speed[1]);
            // Serial.write("\n");
            return;
        default:
            lastRead = NENHUMA;
            // Serial.write("DEFAULT!\n");
            return;
    }
}

void controlaBombaGiro(){
    // Serial.write("controlaBombaGiro");
    while(Serial.available() <= 0)
        delay(10);
    peRead = Serial.read();
    switch(lastRead){
        case BOMBA:
            if(peRead == APERTOU){
                //liga a saida da bomba
            }else if(peRead == SOLTOU){
                //desliga a saida da bomba.
            }
            break;
        case NEON:
            if(peRead == APERTOU){
                //liga o boolean que mexe na treta
            }else if(peRead == SOLTOU){
                //desliga o boolean que mexe na treta.
            }
            break;
        case PARA:
            if(peRead == APERTOU || peRead == SOLTOU){
                stopAll();
            }
    }

}
//Calcula a velocidade que cada motor deve girar para mover o veiculo na direção proposta.
void calculateSpeed(){
    unsigned char frente, lado;
    frente = speed[0];
    lado = speed[1];
    if(frente == 0 && lado == 0){
            Serial.write("PAROU TUDO!");
            Serial.write("\n");
            stopAll();
        return;
    }
    unsigned char motoresOposto;
    unsigned char motoresEste;
    bool reverseSide = false;
    if(direction[VERTICAL]){ //FRENTE
            Serial.write("FRENTE!");
            Serial.write("\n");
        if(frente > lado){
            motoresOposto = frente;
            motoresEste = frente-lado;
            reverseSide = false;
        }else if(frente < lado){
            motoresOposto = frente;
            motoresEste = lado-frente;
            reverseSide = true;
        }else{
            motoresOposto = frente;
            motoresEste = 0;
        }
        if(direction[HORIZONTAL]){ //ESQUERDA
            Serial.write("ESQUERDA!");
            Serial.write("\n");
            motorR1.setSpeed(motoresOposto);
            motorR2.setSpeed(motoresOposto);
            motorL1.setSpeed(motoresEste);
            motorL2.setSpeed(motoresEste);
            Serial.write("SpdRgt: \'");
            Serial.write(motoresOposto);
            Serial.write("\'    SpdLft: \'");
            Serial.write(motoresEste);
            Serial.write("\'\n");
            motorR1.run(FORWARD);
            motorR2.run(FORWARD);
            Serial.write("DirRgt: ");
            Serial.write("FORWARD");
            if(motoresEste == 0){
                motorL1.run(RELEASE);
                motorL2.run(RELEASE);
            Serial.write("    DirLft: ");
            Serial.write("RELEASE");
            Serial.write("\n");
            }else if(reverseSide){
                motorL1.run(BACKWARD);
                motorL2.run(BACKWARD);
            Serial.write("    DirLft: ");
            Serial.write("BACKWARD");
            Serial.write("\n");
            }else{
                motorL1.run(FORWARD);
                motorL2.run(FORWARD);
            Serial.write("    DirLft: ");
            Serial.write("FORWARD");
            Serial.write("\n");
            }
        }
        else{ //DIREITA
            Serial.write("DIREITA!");
            Serial.write("\n");
            motorR1.setSpeed(motoresEste);
            motorR2.setSpeed(motoresEste);
            motorL1.setSpeed(motoresOposto);
            motorL2.setSpeed(motoresOposto);
            Serial.write("SpdRgt: \'");
            Serial.write(motoresEste);
            Serial.write("\'    SpdLft: \'");
            Serial.write(motoresOposto);
            Serial.write("\'\n");
            motorL1.run(FORWARD);
            motorL2.run(FORWARD);
            Serial.write("DirLft: ");
            Serial.write("FORWARD");
            if(motoresEste == 0){
                motorR1.run(RELEASE);
                motorR2.run(RELEASE);
            Serial.write("    DirRgt: ");
            Serial.write("RELEASE");
            Serial.write("\n");
            }else if(reverseSide){
                motorR1.run(BACKWARD);
                motorR2.run(BACKWARD);
            Serial.write("    DirRgt: ");
            Serial.write("BACKWARD");
            Serial.write("\n");
            }else{
                motorR1.run(FORWARD);
                motorR2.run(FORWARD);
            Serial.write("    DirRgt: ");
            Serial.write("FORWARD");
            Serial.write("\n");
            }

        }
    }else{ //TRAS
        if(frente > lado){
            Serial.write("TRAS!");
            Serial.write("\n");
            
            motoresOposto = frente;
            motoresEste = frente-lado;
            reverseSide = false;
        }else if(lado > frente){
            motoresOposto = frente;
            motoresEste = lado-frente;
            reverseSide = true;
        }else{
            motoresOposto = frente;
            motoresEste = 0;
        }
        if(direction[HORIZONTAL]){ //ESQUERDA
            Serial.write("ESQUERDA!");
            Serial.write("\n");
            motorR1.setSpeed(motoresOposto);
            motorR2.setSpeed(motoresOposto);
            motorL1.setSpeed(motoresEste);
            motorL2.setSpeed(motoresEste);
            Serial.write("SpdRgt: \'");
            Serial.write(motoresOposto);
            Serial.write("\'    SpdLft: \'");
            Serial.write(motoresEste);
            Serial.write("\'\n");
            motorR1.run(BACKWARD);
            motorR2.run(BACKWARD);
            Serial.write("DirRgt: ");
            Serial.write("BACKWARD");
            if(motoresEste == 0){
                motorL1.run(RELEASE);
                motorL2.run(RELEASE);
            Serial.write("    DirLft: ");
            Serial.write("RELEASE");
            Serial.write("\n");
            }else if(reverseSide){
                motorL1.run(FORWARD);
                motorL2.run(FORWARD);
            Serial.write("    DirLft: ");
            Serial.write("FORWARD");
            Serial.write("\n");
            }else{
                motorL1.run(BACKWARD);
                motorL2.run(BACKWARD);
            Serial.write("    DirLft: ");
            Serial.write("BACKWARD");
            Serial.write("\n");
            }
        }
        else{ //DIREITA
            Serial.write("DIREITA!");
            Serial.write("\n");
            motorR1.setSpeed(motoresEste);
            motorR2.setSpeed(motoresEste);
            motorL1.setSpeed(motoresOposto);
            motorL2.setSpeed(motoresOposto);
            Serial.write("SpdRgt: \'");
            Serial.write(motoresEste);
            Serial.write("\'    SpdLft: \'");
            Serial.write(motoresOposto);
            Serial.write("\'\n");
            motorL1.run(BACKWARD);
            motorL2.run(BACKWARD);
            Serial.write("DirLft: ");
            Serial.write("BACKWARD");
            if(motoresEste == 0){
                motorR1.run(RELEASE);
                motorR2.run(RELEASE);
            Serial.write("    DirRgt: ");
            Serial.write("RELEASE");
            Serial.write("\n");
            }else if(reverseSide){
                motorR1.run(FORWARD);
                motorR2.run(FORWARD);
            Serial.write("    DirRgt: ");
            Serial.write("FORWARD");
            Serial.write("\n");
            }else{
                motorR1.run(BACKWARD);
                motorR2.run(BACKWARD);
            Serial.write("    DirRgt: ");
            Serial.write("BACKWARD");
            Serial.write("\n");
            }
        }

    }
}
void stopAll(){
    motorL1.setSpeed(0);
    motorL1.run(RELEASE);
    motorL2.setSpeed(0);
    motorL2.run(RELEASE);
    motorR1.setSpeed(0);
    motorR1.run(RELEASE);
    motorR2.setSpeed(0);
    motorR2.run(RELEASE);
}