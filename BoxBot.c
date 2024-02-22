//+------------------------------------------------------------------+
//|                                                       BoxBot.mq5 |
//|                                          Copyright 2024, Stefano |
//+------------------------------------------------------------------+
#property copyright "Copyright 2023, Stefano"
#property version   "1.00"

// Ajustar ENUM para hora ou validar hora
// Ajustar ENUM para minuto ou validar minuto
// Ajustar lote ou validar tamanho do lote correto
// Add entrar MENOS/MAIS e incluir porcentagem de calculo de entrada
// Validação já existe ordem para este ativo? Se tiver não enviar!

enum ENUM_OPERAR {
    sim = 1, // Sim
    nao = 0  // Não
};

enum ENUM_QUANDO_ENTRAR {
    cair  = 1, // Cair %
    subir = 0  // Subir %
};

enum ENUM_TIPO_ORDEM {
    comprado = 1, // Comprar
    vendido  = 0  // Vender
};

input group           "--- Boleta"
input int                lote         = 100; // Tamanho do lote
input ENUM_QUANDO_ENTRAR tipo_entrada = 1;   // Entrar quando?
input double             porcentagem  = 1.0; // Qual a porcentagem?
input ENUM_TIPO_ORDEM    tipo_ordem   = 1;   // Comprar ou vender?

input group           "--- Horario de entrada"
input int entrada_hora   = 9;  // Hora
input int entrada_minuto = 55; // Minuto

input group           "--- Horario de saida"
input int saida_hora   = 16; // Hora
input int saida_minuto = 55; // Minuto

input group           "--- Dia de operação"
input ENUM_OPERAR domingo = 0; // Operar no domingo?
input ENUM_OPERAR segunda = 1; // Operar na segunda-feira?
input ENUM_OPERAR terca   = 1; // Operar na terça-feira?
input ENUM_OPERAR quarta  = 1; // Operar na quarta-feira?
input ENUM_OPERAR quinta  = 1; // Operar na quinta-feira?
input ENUM_OPERAR sexta   = 1; // Operar na sexta-feira?
input ENUM_OPERAR sabado  = 0; // Operar no sabado?

bool trabalhando = false;

int OnInit() {
    EventSetTimer(60);
    return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason) {
    EventKillTimer();
}

void OnTimer() {
    if (trabalhando == false && hojeTemOperacao() && horaDeEnviarOrdens()) {
        enviarOrdens();
        trabalhando = true;
    }

    if (trabalhando == true && hojeTemOperacao() && horaDeFecharOrdens()) {
        fecharOrdens();
        trabalhando = false;
    }
}

bool horaDeEnviarOrdens() {
    MqlDateTime hora;
    TimeToStruct(TimeCurrent(), hora);

    if (hora.hour == entrada_hora && hora.min == entrada_minuto) {
        return true;
    }

    return false;
}

bool horaDeFecharOrdens() {
    MqlDateTime hora;
    TimeToStruct(TimeCurrent(), hora);

    if (hora.hour == saida_hora && hora.min == saida_minuto) {
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
            if (domingo == 1) {
                temOperacaoHoje = true;   
            }
            break;

       case 1:
           if (segunda == 1) {
               temOperacaoHoje = true;   
           }
           break;

       case 2:
           if (terca == 1) {
               temOperacaoHoje = true;   
           }
           break;

       case 3:
           if (quarta == 1) {
               temOperacaoHoje = true;   
           }
           break;

       case 4:
           if (quinta == 1) {
               temOperacaoHoje = true;   
           }
           break;

       case 5:
           if (sexta == 1) {
               temOperacaoHoje = true;   
           }
           break;

       case 6:
           if (sabado == 1) {
               temOperacaoHoje = true;   
           }
           break;

       default:
           temOperacaoHoje = false;
           break;
    }

    return temOperacaoHoje;
}

void enviarOrdens() {

}

void fecharOrdens() {

}
