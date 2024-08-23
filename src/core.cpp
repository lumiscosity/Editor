/*
 * This file is part of EasyRPG Editor.
 *
 * EasyRPG Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Editor. If not, see <http://www.gnu.org/licenses/>.
 */

#include "core.h"
#include <QApplication>
#include <QBitmap>
#include <QBrush>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>
#include "common/dbstring.h"
#include "common/image_loader.h"
#include "defines.h"

//define static member
Core *Core::core_instance = nullptr;

Core& core() {
	return *Core::getCore();
}

Core::Core()
{
	m_tileSize = 16;
	m_tool = PENCIL;
	m_layer = LOWER;
	m_lowerSel.push_back(0);
	m_upperSel.push_back(10000);
	m_lowerSelW = 1;
	m_upperSelW = 1;
	m_lowerSelH = 1;
	m_upperSelH = 1;
    m_eventSel = 10000;

	m_runGameDialog = nullptr;
}

Core *Core::getCore()
{
	if (!core_instance) {
		core_instance = new Core();
	}
	return core_instance;
}

int Core::tileSize()
{
	return m_tileSize;
}

void Core::setTileSize(int tile_size)
{
	m_tileSize = tile_size;
}

QString Core::rtpPath(const QString &folder, const QString &filename) const
{
	return m_rtpDir+folder+filename;
}

Core::Layer Core::layer()
{
	return m_layer;
}

void Core::setLayer(const Layer &current_layer)
{
	m_layer = current_layer;
	emit layerChanged();
}
Core::Tool Core::tool()
{
	return m_tool;
}

void Core::setTool(const Tool &current_tool)
{
	m_tool = current_tool;
	emit toolChanged();
}

QString Core::defDir() const
{
	return m_defDir;
}

void Core::setDefDir(const QString &defDir)
{
	m_defDir = defDir + (defDir.endsWith('/') ? "" : "/");
}

void Core::runGame()
{
	if (!m_runGameDialog)
		m_runGameDialog = new RunGameDialog(project()->projectData());
	m_runGameDialog->exec();
}

void Core::runGameHere(int map_id, int x, int y)
{
	if (!m_runGameDialog)
		m_runGameDialog = new RunGameDialog(project()->projectData());
	m_runGameDialog->runHere(map_id, x, y);
}

void Core::runBattleTest(int troop_id)
{
	if (!m_runGameDialog)
		m_runGameDialog = new RunGameDialog(project()->projectData());
    //Set parameters
	m_runGameDialog->runBattle(troop_id);
}

std::shared_ptr<Project>& Core::project() {
	return m_project;
}

const std::shared_ptr<Project>& Core::project() const {
	return m_project;
}

void Core::setRtpDir(const QString &n_path)
{
	m_rtpDir = n_path;
}

short Core::selection(int off_x, int off_y)
{
	short result = 0;
	switch(m_layer)
	{
	case LOWER:
		off_x %= m_lowerSelW;
		off_y %= m_lowerSelH;
		if (off_x < 0)
			off_x += m_lowerSelW;
		if (off_y < 0)
			off_y += m_lowerSelH;
		result = m_lowerSel[static_cast<size_t>(off_x+off_y*m_lowerSelW)];
		break;
	case UPPER:
		off_x %= m_upperSelW;
		off_y %= m_upperSelH;
		if (off_x < 0)
			off_x += m_upperSelW;
		if (off_y < 0)
			off_y += m_upperSelH;
		result = m_upperSel[static_cast<size_t>(off_x+off_y*m_upperSelW)];
		break;
	case EVENT:
		result = m_eventSel;
		break;
	}
	return result;
}

int Core::selWidth()
{
	int w = 1;
	if (m_layer == LOWER)
		w = m_lowerSelW;
	if (m_layer == UPPER)
		w = m_upperSelW;
	return w;
}

int Core::selHeight()
{
	int h = 1;
	if (m_layer == LOWER)
		h = m_lowerSelH;
	if (m_layer == UPPER)
		h = m_upperSelH;
	return h;
}

void Core::setSelection(std::vector<short> n_sel, int n_w, int n_h)
{
	if (static_cast<int>(n_sel.size()) != n_w * n_h)
		return;
	switch(m_layer)
	{
	case LOWER:
		m_lowerSel = n_sel;
		m_lowerSelW = n_w;
		m_lowerSelH = n_h;
		break;
	case UPPER:
		m_upperSel = n_sel;
		m_upperSelW = n_w;
		m_upperSelH = n_h;
		break;
	case EVENT:
		m_eventSel = n_sel[0];
		break;
	}
}

void Core::cacheEvent(const lcf::rpg::Event* ev, QString key) {
	
	if (ev->pages.empty())
		return;

	const lcf::rpg::EventPage& evp = ev->pages[0];
	if (evp.character_name.empty())
		return;

	QString char_name = ToQString(evp.character_name);

	QPixmap charset(ImageLoader::Load(project()->findFile(CHARSET,char_name, FileFinder::FileType::Image)));
	if (!charset)
		charset = ImageLoader::Load(rtpPath(CHARSET,char_name));
	if (!charset)
	{
		qWarning()<<"CharSet"<<char_name<<"not found.";
		charset = createDummyPixmap(288,256);
	}

	int char_index = evp.character_index;
    int src_x = (char_index%4)*charset.width()/4 + evp.character_pattern * charset.width()/12;
    int src_y = (char_index/4)*charset.height()/2 + evp.character_direction * charset.height()/8;

	m_eventCache[key] = charset.copy(src_x, src_y, 24, 32);
}

QPixmap Core::createDummyPixmap(int width, int height)
{
	QPixmap dummy(QPixmap(480,256));
	QPainter p(&dummy);
	p.drawTiledPixmap(0, 0, width, height, QPixmap(":/embedded/share/old_grid.png"));
	p.end();
	return dummy;
}

QMap<QString, QPixmap> &Core::getEventCache() {
    return m_eventCache;
}
