#ifndef COLORMAPS_HH
#define COLORMAPS_HH

#include <gtk/gtk.h>

#include<colormappable.hh>

class Colormaps
{
private:
  GtkListStore* filenames;

private:
  Colormaps();
  ~Colormaps();

public:
  static Colormaps& getInstance();
  
  GtkListStore* getFileNames();

  void select(GtkTreeIter iter, PresentationInterface::Ptr p);
};

enum
  {
    COLUMN_NAME,
    COLUMN_POINTER,
    N_COLUMNS
  };

#endif
