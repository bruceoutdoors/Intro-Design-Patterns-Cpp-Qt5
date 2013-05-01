#include "dbutils.h"

// TODO: Check if there are other characters that need escaping!

QString DbUtils::escape(QString str) {
    return str.replace("\"", "\\\"");
}

