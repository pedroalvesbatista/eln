// App/PageEditor.cpp - This file is part of eln

/* eln is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   eln is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eln.  If not, see <http://www.gnu.org/licenses/>.
*/

// PageEditor.C

#include "PageEditor.h"
#include "PageView.h"
#include "ToolView.h"
#include "Toolbars.h"
#include "SceneBank.h"
#include "Notebook.h"
#include "Navbar.h"
#include "Assert.h"

#include <QDebug>
#include <QKeyEvent>

class HibernationInfo {
public:
  PageView::SavedState state;
};

PageEditor::PageEditor(SceneBank *bank): bank(bank) {
  Notebook *nb = bank->book();
  hibernation = 0;
  initialize();

  setContentsMargins(0, 0, 0, 0);
  setAttribute(Qt::WA_DeleteOnClose, true);

  QString ttl = nb->bookData()->title();
  QString appname = "eln";
#ifndef QT_NO_DEBUG
  appname += " (debug vsn)";
#endif
  setWindowTitle(ttl.replace(QRegExp("\\s\\s*"), " ") + " - " + appname);
}

bool PageEditor::isHibernating() const {
  return hibernation;
}

void PageEditor::hibernate() {
  ASSERT(view);
  if (!hibernation)
    hibernation = new HibernationInfo;
  hibernation->state = view->saveState();

  delete toolview;
  toolview = 0;
  delete view;
  view = 0;
  bank = 0;
}

void PageEditor::unhibernate(SceneBank *b) {
  ASSERT(hibernation);
  ASSERT(!view);

  bank = b;
  
  initialize();
  view->restoreState(hibernation->state);
  delete hibernation;
  hibernation = 0;
}

void PageEditor::initialize() {
  view = new PageView(bank, this);
  toolview = new ToolView(view->mode(), view);

  connect(toolview->toolbars()->navbar(), SIGNAL(goTOC(Qt::KeyboardModifiers)),
	  view, SLOT(goTOC(Qt::KeyboardModifiers)));
  connect(toolview->toolbars()->navbar(), SIGNAL(goFind()),
	  view, SLOT(openFindDialog()));
  connect(toolview->toolbars()->navbar(), SIGNAL(goPrint()),
	  view, SLOT(openPrintDialog()));
  connect(toolview->toolbars()->navbar(), SIGNAL(goEnd(Qt::KeyboardModifiers)),
	  view, SLOT(lastPage(Qt::KeyboardModifiers)));
  connect(toolview->toolbars()->navbar(),
	  SIGNAL(goRelative(int, Qt::KeyboardModifiers)),
	  view, SLOT(goRelative(int, Qt::KeyboardModifiers)));

  connect(view, SIGNAL(onEntryPage(int, int)),
	  toolview->toolbars(), SLOT(showTools()));
  connect(view, SIGNAL(onFrontMatter(int)),
	  toolview->toolbars(), SLOT(hideTools()));
  connect(view, SIGNAL(scaled(double)),
	  toolview, SLOT(setScale(double)));

  connect(toolview, SIGNAL(drop(QDropEvent)),
	  view, SLOT(drop(QDropEvent)));
   
  toolview->setGeometry(0, 0, width(), height());
  setCentralWidget(view);
  view->gotoFront();  
}

PageEditor::~PageEditor() {
  if (hibernation)
    delete hibernation;
}

void PageEditor::resizeEvent(QResizeEvent *e) {
  QMainWindow::resizeEvent(e);
  if (toolview)
    toolview->setGeometry(0, 0, width(), height());
}

PageEditor *PageEditor::newEditor() {
  ASSERT(view);
  PageEditor *editor = new PageEditor(bank);
  editor->resize(size());
  switch (view->section()) {
  case PageView::Front:
    break;
  case PageView::TOC:
    editor->gotoTOC(view->pageNumber());
    break;
  case PageView::Entries:
    editor->gotoEntryPage(view->pageName());
    break;
  }
  editor->show();
  emit newEditorCreated(editor);
  return editor;
}

void PageEditor::keyPressEvent(QKeyEvent *e) {
  if (isHibernating())
    return;
  
  bool take = false;
  switch (e->key()) {
  case Qt::Key_F12:
    newEditor();
    take = true;
    break;
  default:
    break;
  }

  if (take)
    e->accept();
  else
    QMainWindow::keyPressEvent(e);
}

void PageEditor::gotoEntryPage(QString s) {
  if (view)
    view->gotoEntryPage(s);
}

void PageEditor::gotoTOC(int n) {
  if (view)
    view->gotoTOC(n);
}

void PageEditor::gotoFront() {
  if (view)
    view->gotoFront();
}

void PageEditor::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  if (toolview && e->type()==QEvent::WindowStateChange)
    toolview->setFullScreen(windowState() & Qt::WindowFullScreen);
}