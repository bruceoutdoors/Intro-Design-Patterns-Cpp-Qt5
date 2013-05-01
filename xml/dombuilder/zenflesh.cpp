#include <QTextStream>
#include <docbookdoc.h>

/** An example program that builds documents in a declarative way
   using the docbook library and the Qt XML DOM parser and generator. */

class ZenFlesh : public DocbookDoc {
    public: ZenFlesh();
};

ZenFlesh::ZenFlesh() : 
    DocbookDoc("Zen Flesh, Zen Bones") {

    chapter("101 Zen Stories");
    section("A cup of tea");
    para("Nan-in served a cup of tea.");
    section("Great Waves");
    QDomElement p = para("o-nami the wrestler sat in meditation and "
            "tried to imagine himself as a bunch of great waves.");
    setRole(p, "remark");
    chapter("The Gateless Gate");
    formalpara("The Gateless Gate",
      "In order to enter the gateless gate, you must have a ");
    bold(" mindless mind.");

    section("Joshu's dog");
    para("Has a dog buddha nature or not?");

    section("Haykujo's Fox");
    QDomElement fp = formalpara("This is a special topic", 
       "Which should have a role= remark attribute");
    setRole(fp, "remark");
}

int main() {
   QTextStream cout(stdout);
   ZenFlesh book;
   cout << book << endl;
}

