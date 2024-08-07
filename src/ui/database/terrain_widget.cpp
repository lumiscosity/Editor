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

#include "terrain_widget.h"
#include "common/lcf_widget_binding.h"
#include "ui_terrain_widget.h"

TerrainWidget::TerrainWidget(ProjectData& project, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TerrainWidget),
	m_project(project)
{
	ui->setupUi(this);

    LcfWidgetBinding::connect(this, ui->nameLineEdit);
    LcfWidgetBinding::connect<int32_t>(this, ui->damageSpinBox);
    LcfWidgetBinding::connect<int32_t>(this, ui->encounterRateSpinBox);
    // TODO: background_name
    LcfWidgetBinding::connect<bool>(this, ui->vehicleBoatPassCheckBox);
    LcfWidgetBinding::connect<bool>(this, ui->vehicleShipPassCheckBox);
    LcfWidgetBinding::connect<bool>(this, ui->vehicleAirshipPassCheckBox);
    LcfWidgetBinding::connect<bool>(this, ui->vehicleAirshipLandCheckBox);

}

TerrainWidget::~TerrainWidget()
{
	delete ui;
}

void TerrainWidget::setData(lcf::rpg::Terrain* terrain)
{
    m_current = terrain ? terrain : &m_dummy;

    LcfWidgetBinding::bind(ui->nameLineEdit, m_current->name);
    LcfWidgetBinding::bind(ui->damageSpinBox, m_current->damage);
    LcfWidgetBinding::bind(ui->encounterRateSpinBox, m_current->encounter_rate);
    // TODO: background_name
    LcfWidgetBinding::bind(ui->vehicleBoatPassCheckBox, m_current->boat_pass);
    LcfWidgetBinding::bind(ui->vehicleShipPassCheckBox, m_current->ship_pass);
    LcfWidgetBinding::bind(ui->vehicleAirshipPassCheckBox, m_current->airship_pass);
    LcfWidgetBinding::bind(ui->vehicleAirshipLandCheckBox, m_current->airship_land);
    // TODO: bind player covering radio buttons to bush_depth


    this->setEnabled(terrain != nullptr);
}
