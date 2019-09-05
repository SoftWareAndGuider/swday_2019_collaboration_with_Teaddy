int ResetSW = 0;    //재시작 스위치 핀 번호
int piezo = 8;   //게임소리용 피에조 부저
int led[] = {1, 2, 3, 4, 5};            //두더지 5마리
int sw[] = {A0, A1, A2, A3, A4}; //두더지 잡는 스위치 5개
int life[] = {10, 11, 12, 13}; //try 3번
int ending = 1;     //게임종료용 변수
int dudog = 0;      //두더지 잡은 수
int fin = 5;          //잡을 두더지 마리 수
int TRY = 3;      //Life
long randNumber;  //무작위로 튀어나올 두더지와 스위치 번호
int i;
int j;

void setup() {
    for(i=0; i<5; i++) {
        pinMode(led[i], OUTPUT);        //1~5번 두더지 사용
        pinMode(sw[i], INPUT_PULLUP);   //1~5번 두더지 스위치 사용(풀업)
    }
    for(j=0; j<4; j++) {
        pinMode(life[j], OUTPUT);        //1~3번 life 사용
    }
    pinMode(ResetSW, INPUT_PULLUP);     //리셋용 스위치 사용(풀업)
    pinMode(piezo, OUTPUT);       //게임소리 부저 사용
//
//    digitalWrite(1, HIGH);
//    digitalWrite(2, HIGH);
//    digitalWrite(3, HIGH);
//    digitalWrite(4, HIGH);
//    digitalWrite(5, HIGH);
}

void loop() {
    if(ending==1) {
        //게임 재시작 스위치 입력 시 (게임종료에 관한 변수 초기화)
        if(digitalRead(ResetSW) == LOW) {    
            ending = 0;
            dudog=0;
            TRY = 3;

            //게임 시작 소리
            tone(piezo, 880);  //5옥 라
            delay(200);
            tone(piezo, 932.33);  //5옥 라
            delay(200);
            noTone(piezo);

            for(j=0; j<4; j++) {
              digitalWrite(life[j], HIGH);
            }
        }

    } else if (dudog==fin) {
        //엔딩 소리 (빠밤~빠밤빠~ 소라!)
        tone(piezo, 523);  
        delay(250);
        noTone(piezo);
        tone(piezo, 392);  
        delay(125);
        noTone(piezo);
        tone(piezo, 440);  
        delay(125);
        noTone(piezo);
        tone(piezo, 392);  
        delay(250);
        noTone(piezo);
        tone(piezo, 0);  
        delay(250);
        noTone(piezo);
        tone(piezo, 494);  
        delay(250);
        noTone(piezo);
        tone(piezo, 523);  
        delay(250);
        noTone(piezo);     //소리 끄기

        for(j=0; j<4; j++) {
          digitalWrite(life[j], LOW); //LED 끄기
        }
        ending = 1; //엔딩소리 더 이상 출력 안함 + 게임종료

    } else if (TRY==0) { //3번 이상 놓친 경우 게임 종료
        tone(piezo, 523);  
        delay(1000);
        noTone(piezo);     //소리 끄기
        ending = 1; //엔딩소리 더 이상 출력 안함 + 게임종료

    } else {
      randNumber = random(0,4); // 0번~4번 두더지까지 무작위로 선정!
        switch(randNumber) {
        case 0:
            dudogi();
            break;
        case 1:
            dudogi();
            break;
        case 2:
            dudogi();
            break;
        case 3:
            dudogi();
            break;
        case 4:
            dudogi();
            break;
        }

    }
        digitalWrite(life[TRY], LOW); //실수한 경우 Life LED 하나씩 끄기
        delay(1000); // 다음 두더지 튀어나올 대기시간
}

void dudogi() {
    for (int count=0; count < 10; count++) { 
        if (dudog==fin) {    // 모든 두더지 잡았을 경우 for문 아웃->게임종료 
                            // for문 시작전 판단한다.
            break;
        } else if(TRY == 0){
          break;

        } else if (digitalRead(sw[randNumber]) == LOW) {
            digitalWrite(led[randNumber], LOW);

            //두더지 죽는 소리
            tone(piezo, 440);  //솔
            delay(50);
            noTone(piezo);
            delay(50);
            tone(piezo, 440);  //솔
            delay(50);
            noTone(piezo);
            delay(50);
            tone(piezo, 523);  //라
            delay(200);
            noTone(piezo);     //소리 끄기         
            dudog++; // 두더지 잡은 숫자 증가
            TRY++;
            break; // 두더지 잡으면 for문 종료해서 다른 두더지 찾음.

        } else    // 두더지 튀어나오기!
        digitalWrite(led[randNumber], HIGH);
        delay(50); // 0.05초마다 입력들어왔는지 확인
        digitalWrite(led[randNumber], LOW); // 0.5초동안 입력 없으면 불 꺼짐.  
        }
        TRY--;
    
}
