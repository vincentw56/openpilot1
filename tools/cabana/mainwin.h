#pragma once

#include <QDockWidget>
#include <QJsonDocument>
#include <QMainWindow>
#include <QProgressBar>
#include <QSplitter>
#include <QStatusBar>

#include "tools/cabana/chartswidget.h"
#include "tools/cabana/detailwidget.h"
#include "tools/cabana/messageswidget.h"
#include "tools/cabana/videowidget.h"
#include "tools/cabana/tools/findsimilarbits.h"

const QString AUTO_SAVE_EXTENSION = ".tmp";

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  void dockCharts(bool dock);
  void showStatusMessage(const QString &msg, int timeout = 0) { statusBar()->showMessage(msg, timeout); }
  void loadFile(const QString &fn);

public slots:
  void openRoute();
  void newFile();
  void openFile();
  void openRecentFile();
  void openOpendbcFile();
  void loadDBCFromOpendbc(const QString &name);
  void loadDBCFromFingerprint();
  void loadDBCFromClipboard();
  void save();
  void saveAs();
  void saveDBCToClipboard();

signals:
  void showMessage(const QString &msg, int timeout);
  void updateProgressBar(uint64_t cur, uint64_t total, bool success);

protected:
  void remindSaveChanges();
  void saveFile(const QString &fn);
  void autoSave();
  void cleanupAutoSaveFile();
  void setCurrentFile(const QString &fn);
  void updateRecentFileActions();
  void createActions();
  void createDockWindows();
  void createStatusBar();
  void createShortcuts();
  void closeEvent(QCloseEvent *event) override;
  void DBCFileChanged();
  void updateDownloadProgress(uint64_t cur, uint64_t total, bool success);
  void setOption();
  void findSimilarBits();
  void undoStackCleanChanged(bool clean);
  void undoStackIndexChanged(int index);
  void onlineHelp();
  void toggleFullScreen();
  void updateStatus();

  VideoWidget *video_widget = nullptr;
  QDockWidget *video_dock;
  MessagesWidget *messages_widget;
  CenterWidget *center_widget;
  ChartsWidget *charts_widget;
  QWidget *floating_window = nullptr;
  QVBoxLayout *charts_layout;
  QProgressBar *progress_bar;
  QLabel *status_label;
  QJsonDocument fingerprint_to_dbc;
  QSplitter *video_splitter;;
  QString current_file = "";
  enum { MAX_RECENT_FILES = 15 };
  QAction *recent_files_acts[MAX_RECENT_FILES] = {};
  QMenu *open_recent_menu = nullptr;
  int prev_undostack_index = 0;
  int prev_undostack_count = 0;
  friend class OnlineHelp;
};

class HelpOverlay : public QWidget {
  Q_OBJECT
public:
  HelpOverlay(MainWindow *parent);

protected:
  void drawHelpForWidget(QPainter &painter, QWidget *w);
  void paintEvent(QPaintEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  bool eventFilter(QObject *obj, QEvent *event) override;
};
