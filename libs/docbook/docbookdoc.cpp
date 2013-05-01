#include "docbookdoc.h"

DocbookDoc::DocbookDoc(QString titleString) {
    Element root = createElement("book");
    appendChild(root);
    title(titleString, root);
    currentParent = root; 
}
//start id=elements
Element DocbookDoc::bridgehead(QString titleStr) {
    Element retval = createElement("bridgehead");
    Element titleEl = title(titleStr);
    currentParent.appendChild(retval);
    return retval;
}
Element DocbookDoc::title(QString name, Element parent) {
    Element retval = createElement("title");
    QDomText tn = createTextNode(name);
    retval.appendChild(tn);
    if (parent != Element())
        parent.appendChild(retval);
    return retval;
}

Element DocbookDoc::chapter(QString titleString) {
    Element chapter = createElement("chapter");
    title(titleString, chapter);
    documentElement().appendChild(chapter);
    currentParent = chapter;
    currentChapter = chapter;
    return chapter;
}

Element DocbookDoc::para(QString textstr) {
    QDomText tn = createTextNode(textstr);
    Element para = createElement("para");
    para.appendChild(tn);
    currentParent.appendChild(para);
    currentPara = para;
    return para;
}
//end

QString DocbookDoc::getTitle(Element element) const {
    QString retval;
    QDomNode titleNode = element.elementsByTagName("title").item(0);
    if (titleNode != QDomNode()) {
        Element el = titleNode.toElement();
        QString text = el.text();
        retval = text;
    }
    return retval;
}

Element DocbookDoc::appendix(QString titleString) {
    Element appendix = createElement("appendix");
    title(titleString, appendix);
    currentParent=appendix;
    return appendix;
}

Element DocbookDoc::section(QString titleString) {
    Element section = createElement("section");
    title(titleString, section);
    currentChapter.appendChild(section);
    currentParent = section;
    return section;
}

Element DocbookDoc::listitem() {
    Element li = createElement("listitem");
    currentList.appendChild(li);
    return li;
}    

Element DocbookDoc::orderedlist() {
    Element ol = createElement("orderedlist");
    currentParent.appendChild(ol);
    currentList = ol;
    return ol;
}

Element DocbookDoc::formalpara(QString tit, QString text) {
    Element formalp = createElement("formalpara");
    Element titleElement = title(tit, formalp);
    QDomText tn = createTextNode(text);
    formalp.appendChild(tn);
    currentParent.appendChild(formalp);
    return formalp;
}

//start id=text
Element DocbookDoc::bold(QString text) {
    QDomText tn = createTextNode(text);
    Element emphasis = createElement("emphasis");
    setRole(emphasis, "strong");
    emphasis.appendChild(tn);
    currentPara.appendChild(emphasis);
    return emphasis;
}

void  DocbookDoc::setRole(Element el, QString role) {
    el.setAttribute("role", role);    
}
//end

Element DocbookDoc::xref(QString id) {
    Element retval = createElement("xref");
    retval.setAttribute("linkend", id);
    return retval;
}

Element DocbookDoc::xrefP(QString id) {
    Element xr = xref(id);
    QDomText open = createTextNode("(");
    QDomText close = createTextNode(")");
    Element para = createElement("para");
    para << open;
    para << xr;
    para << close;
    return para;
}


Element DocbookDoc::simplesect(QString titleStr) {
    QDomElement retval = createElement("simplesect");
    QDomElement titleEl = title(titleStr, retval);
    currentParent = retval;
    return retval;
}
//end
