#ifndef REGLAS_H
#define REGLAS_H

#include <QObject>

class Reglas : public QObject
{
    Q_OBJECT

public:
    explicit Reglas(QObject *parent = nullptr);

    // Función para verificar si se ha cumplido una condición para pasar de nivel
    bool verificarProgreso(int objetosRecogidos, int totalObjetos);

signals:
    // Señal para indicar que se ha pasado al siguiente nivel
    void nivelCompletado();

private:
    int nivelActual;
    int totalNiveles;
};

#endif // REGLAS_H
