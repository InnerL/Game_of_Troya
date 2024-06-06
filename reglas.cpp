#include "reglas.h"

Reglas::Reglas(QObject *parent)
    : QObject(parent), nivelActual(1), totalNiveles(3) // Por ejemplo, 3 niveles
{
}

bool Reglas::verificarProgreso(int objetosRecogidos, int totalObjetos)
{
    if (objetosRecogidos >= totalObjetos) {
        if (nivelActual < totalNiveles) {
            nivelActual++;
            emit nivelCompletado();
            return true;
        }
    }
    return false;
}
