#include <QXmlStreamWriter>
#include <QString>

#include "action.h"

QString Action::establishConnection(QString nombreTienda) {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"EstablishConnection.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "ESTABLISH_CONNECTION");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("tienda", nombreTienda);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askMarcasInfo() {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"MarcasInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MARCAS_INFO_ASK");
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askModelosInfo(int marcaId) {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"ModelosInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MODELOS_INFO_ASK");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("marca_id", QString::number(marcaId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askReparacionInfo(int modeloId) {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"ReparacionInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "REPARACION_INFO_ASK");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("modelo_id", QString::number(modeloId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::error(QString errorMessage) {
    QString message;
    QXmlStreamWriter writer(&message);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD(QString("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"Error.dtd\">"));

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "ERROR");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("message", errorMessage);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

