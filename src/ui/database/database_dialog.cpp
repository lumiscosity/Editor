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
#include "database_dialog.h"
#include "ui_database_dialog.h"
#include <QPushButton>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <lcf/ldb/reader.h>
#include "database_split_widget.h"

DatabaseDialog::DatabaseDialog(ProjectData& project, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DatabaseDialog),
	m_project(project)
{
    ui->setupUi(this);

	m_projectDataCopy = project;

	pageActors = new DatabaseSplitWidget<lcf::rpg::Actor>(m_projectDataCopy, this);
	pageClasses = new DatabaseSplitWidget<lcf::rpg::Class>(m_projectDataCopy, this);
	pageSkills = new DatabaseSplitWidget<lcf::rpg::Skill>(m_projectDataCopy, this);
	pageItems = new DatabaseSplitWidget<lcf::rpg::Item>(m_projectDataCopy, this);
	pageEnemies = new DatabaseSplitWidget<lcf::rpg::Enemy>(m_projectDataCopy, this);
	pageEnemyGroups = new DatabaseSplitWidget<lcf::rpg::Troop>(m_projectDataCopy, this);
	pageAttributes = new DatabaseSplitWidget<lcf::rpg::Attribute>(m_projectDataCopy, this);
	pageStates = new DatabaseSplitWidget<lcf::rpg::State>(m_projectDataCopy, this);
	pageBattleAnimations = new DatabaseSplitWidget<lcf::rpg::Animation>(m_projectDataCopy, this);
	pageBattleAnimations2 = new DatabaseSplitWidget<lcf::rpg::BattlerAnimation>(m_projectDataCopy, this);
	pageBattleScreen = new BattleScreenWidget(m_projectDataCopy, this);
	pageTerrain = new DatabaseSplitWidget<lcf::rpg::Terrain>(m_projectDataCopy, this);
    pageChipset = new DatabaseSplitWidget<lcf::rpg::Chipset>(m_projectDataCopy, this);
	pageCommonevents = new DatabaseSplitWidget<lcf::rpg::CommonEvent>(m_projectDataCopy, this);
	pageSwitches = new DatabaseSplitWidget<lcf::rpg::Switch>(m_projectDataCopy, this);
	pageVariables = new DatabaseSplitWidget<lcf::rpg::Variable>(m_projectDataCopy, this);

	pageVocabulary = new VocabularyWidget(m_projectDataCopy, this);
	pageSystem = new SystemWidget(m_projectDataCopy, this);
	pageSystem2  = new System2Widget(m_projectDataCopy, this);
	ui->tabOld_Pages->insertTab(0, pageActors, tr("Characters"));
	ui->tabOld_Pages->insertTab(1, pageClasses, tr("Professions"));
	ui->tabOld_Pages->insertTab(2, pageSkills, tr("Skills"));
	ui->tabOld_Pages->insertTab(3, pageItems, tr("Items"));
	ui->tabOld_Pages->insertTab(4, pageEnemies, tr("Enemys"));
	ui->tabOld_Pages->insertTab(5, pageEnemyGroups, tr("EnemyGroup"));
	ui->tabOld_Pages->insertTab(6, pageAttributes, tr("Attributes"));
	ui->tabOld_Pages->insertTab(7, pageStates, tr("Hero Status"));
	ui->tabOld_Pages->insertTab(8, pageBattleAnimations, tr("Battle Animation"));
	ui->tabOld_Pages->insertTab(9, pageBattleAnimations2, tr("Battle Animation 2"));
	ui->tabOld_Pages->insertTab(10, pageBattleScreen, tr("Battle screen"));
	ui->tabOld_Pages->insertTab(11, pageTerrain, tr("Terrain"));
    ui->tabOld_Pages->insertTab(12, pageChipset, tr("Chipset"));
	ui->tabOld_Pages->insertTab(13, pageVocabulary, tr("Vocabulary"));
	ui->tabOld_Pages->insertTab(14, pageSystem, tr("System"));
	ui->tabOld_Pages->insertTab(15, pageSystem2, tr("System"));
	ui->tabOld_Pages->insertTab(16, pageCommonevents, tr("Common events"));
	ui->tabOld_Pages->insertTab(17, pageSwitches, tr("Switches"));
	ui->tabOld_Pages->insertTab(19, pageVariables, tr("Variables"));

	ui->tabOld_Pages->setCurrentWidget(pageActors);
}

DatabaseDialog::~DatabaseDialog()
{
	delete ui;
}

void DatabaseDialog::on_buttonBox_clicked(QAbstractButton *button)
{
	switch(ui->buttonBox->standardButton(button))
	{
		// Standard buttons:
    case QDialogButtonBox::Apply: {
        m_project = m_projectDataCopy;
        lcf::LDB_Reader::PrepareSave(m_project.database());
        core().project()->saveDatabase();
        break;
    }
    case QDialogButtonBox::Ok: {
        m_project = m_projectDataCopy;
        lcf::LDB_Reader::PrepareSave(m_project.database());
        core().project()->saveDatabase();
    }
    default:
        this->close();
        break;
	}
}
