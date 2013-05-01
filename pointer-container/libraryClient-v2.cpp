#include "libraryui.h"
#include "library.h"

bool saved(false);

int main() {
   Library lib;
   LibraryUI libui(&lib);
   while(1) {
      switch(libui.nextTask()) {
      case LibraryUI::READ: libui.read();
         saved = false;
         break;
      case LibraryUI::ADD: libui.enterData();
         saved = false;
         break;
      case LibraryUI::FIND: libui.find();
         break;
      case LibraryUI::REMOVE: libui.remove();
         saved = false;
         break;
      case LibraryUI::SAVE: libui.save();
         saved = true;
         break;
      case LibraryUI::LIST: libui.list();
         break;
      case LibraryUI::QUIT: libui.prepareToQuit(saved);
         break;
      default:
         break;
      }
   }
}

