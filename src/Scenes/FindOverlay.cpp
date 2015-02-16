// FindOverlay.cpp

#include "FindOverlay.H"
#include "SheetScene.H"
#include "TextItem.H"
#include "MarkupData.H"
#include "FindRegion.H"
#include "BlockItem.H"
#include "GfxNoteItem.H"
#include <QDebug>

FindOverlay::FindOverlay(SheetScene *scene, QString phrase) {
  qDebug() << "FindOverlay" << this;
  setZValue(-1);
  foreach (QGraphicsItem *i, scene->items()) {
    TextItem *ti = dynamic_cast<TextItem *>(i);
    if (!ti)
      continue;
    //    BlockItem *bi = ti->ancestralBlock();
    int idx = -1;
    QString txt = ti->data()->text().toLower();
    qDebug() << (void*)ti  << (void*)(ti->ancestralBlock()) << txt;
    while (true) {
      idx = txt.indexOf(phrase, idx+1);
      if (idx<0)
	break;
      MarkupData *md = new MarkupData(idx, idx+phrase.size(),
				      MarkupData::Emphasize, 0);
      QObject *obj = md; obj->setParent(this); // so it will be destroyed
      /*QGraphicsItem *gi = */ new FindRegion(md, ti, this);
    }
  }
  //  startTimer(10000); // self-destruct after 10 seconds

}

FindOverlay::~FindOverlay() {
  qDebug() << "~FindOverlay" << this;
  // children automatically destructed as well
}

void FindOverlay::timerEvent(QTimerEvent *) { // self-destruct
  deleteLater();
}


