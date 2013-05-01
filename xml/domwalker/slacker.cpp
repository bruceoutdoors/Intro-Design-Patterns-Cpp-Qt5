#include <slacker.h>
#include <QTextStream>
/*
  Overridden from DomWalker (base class), this virtual method
  is called from WalkTree on each node. 
  */

//start  
QDomElement Slacker::visit(QDomElement element) {
    QString name = element.tagName();
    
     
    QString cvalue = element.attribute("c", QString()) ;
    if (cvalue != QString()) {                  /* Modifying attributes - any c= becomes condition= */
        element.setAttribute("condition", cvalue);
        element.setAttribute("c", QString());
    }
    //end
    /* For any condition= attribute, add a role=  */
    cvalue = element.attribute("condition", QString());
    if (cvalue != QString()) {
        element.setAttribute("role", cvalue);
    }
    
    // Mapping elements: 
    if (name == "p") {
        element.setTagName("para");
        return element;
    }
    if (name == "ul") {
        element.setTagName("unorderedlist");
        return element;
    }
    //start
    if (name == "b") {
        element.setAttribute("role", "strong");
        element.setTagName("emphasis");
        return element;
    }
    if (name == "li") {                         /* This transformation is more interesting because
        we replace <li> text </li> with 
        <listitem><para> text </para></listitem>. */
        QDomNode parent = element.parentNode();
        QDomElement listitem = createElement("listitem");
        parent.replaceChild(listitem, element); /* Remove the li tag, put a listitem in its place. */
        element.setTagName("para");             /* Modify tag name in-place. */
        listitem.appendChild(element);
        return listitem;
    }
    //end
    
    if (name == "include") { /* replaces the entire <include> 
        node with the contents of a referenced file */
        QDomNode parent = element.parentNode();
        QString filename = element.attribute("src");
        FILE* f = fopen(filename.toAscii(), "r");
        if (f==0) {
            return element;
        }
        QTextStream stream(f, QIODevice::ReadOnly);
        QString text = stream.readAll();
        QDomText tn = this->m_Doc.createTextNode(text);
        QDomElement pl = createElement("programlisting");
        parent.replaceChild(pl, element);
        pl.appendChild(tn);
        return pl;
    }
    return element;
}

