//+------------------------------------------------------------------+
//|                                                       BoxBot.mq5 |
//|                                          Copyright 2024, Stefano |
//+------------------------------------------------------------------+
#property copyright "Copyright 2023, MetaQuotes Ltd."
#property link      "https://www.mql5.com"
#property version   "1.00"

enum ENUM_DIA_SEMANA {
    sim = 1, // Sim
    nao = 0, // Não
};

input group           "--- Boleta"
input int lote = 100;

input group           "--- Horario de entrada"
input int entrada_hora   = 9;  // Hora
input int entrada_minuto = 55; // Minuto

input group           "--- Horario de saida"
input int saida_hora   = 16; // Hora
input int saida_minuto = 55; // Minuto

input group           "--- Dia de operação"
input ENUM_DIA_SEMANA domingo; // Operar no domingo?
input ENUM_DIA_SEMANA segunda; // Operar na segunda-feira?
input ENUM_DIA_SEMANA terca;   // Operar na terça-feira?
input ENUM_DIA_SEMANA quarta;  // Operar na quarta-feira?
input ENUM_DIA_SEMANA quinta;  // Operar na quinta-feira?
input ENUM_DIA_SEMANA sexta;   // Operar na sexta-feira?
input ENUM_DIA_SEMANA sabado;  // Operar no sabado?

int OnInit() {
   EventSetTimer(60);
   return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason) {
   EventKillTimer();
}

void OnTimer() {
   if (hojeTemOperacao() && horaDeEnviarOrdens()) {
   
   }
   
   if (hojeTemOperacao() && horaDeFecharOrdens()) {
   
   }
}

bool horaDeEnviarOrdens() {
   MqlDateTime hora;
   TimeToStruct(TimeCurrent(), hora);
   
   if (hoje.hour == entrada_hora && hoje.min == entrada_minuto) {
      return true;
   }
   
   return false;
}

bool horaDeFecharOrdens() {
   MqlDateTime hora;
   TimeToStruct(TimeCurrent(), hora);
   
   if (hoje.hour == saida_hora && hoje.min == saida_minuto_minuto) {
      return true;
   }
   
   return false;
}

bool hojeTemOperacao() {
   MqlDateTime hoje;
   bool temOperacaoHoje = false;
   TimeToStruct(TimeCurrent(), hoje);
   
   switch(hoje.day_of_week)
   {
      case 0:
         Print("Domingo");
         if (domingo == 1) {
            temOperacaoHoje = true;   
         }
         break;
     case 1:
         Print("Segunda");
         if (segunda == 1) {
            temOperacaoHoje = true;   
         }
         break;
      case 2:
         Print("Terça");
         if (terca == 1) {
            temOperacaoHoje = true;   
         }
         break;
      case 3:
         Print("Quarta");
         if (quarta == 1) {
            temOperacaoHoje = true;   
         }
         break;
      case 4:
         Print("Quinta");
         if (quinta == 1) {
            temOperacaoHoje = true;   
         }
         break;
      case 5:
         Print("Sexta");
         if (sexta == 1) {
            temOperacaoHoje = true;   
         }
         break;
      case 6:
         Print("Sabado");
         if (sabado == 1) {
            temOperacaoHoje = true;   
         }
         break;
      default:
         Print("Nao foi possivel descobrir o dia da semana");
         temOperacaoHoje = false;
         break;
     }
  
   return temOperacaoHoje;
}
