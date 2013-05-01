void AutoSaver::saveIfNecessary() {
    if (!QMetaObject::invokeMethod(parent(), "save")) {
        qWarning() << "AutoSaver: error invoking save() on parent";
    }
}