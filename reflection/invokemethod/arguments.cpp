QByteArray buffer= ... ;
const bool b = QMetaObject::invokeMethod(m_thread, "calculateSpectrum",
                  Qt::AutoConnection,
                  Q_ARG(QByteArray, buffer),
                  Q_ARG(int, format.frequency()),
                  Q_ARG(int, bytesPerSample));
