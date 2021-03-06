/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2018 Icinga Development Team (https://icinga.com/)      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef PERFDATAWRITER_H
#define PERFDATAWRITER_H

#include "perfdata/perfdatawriter-ti.hpp"
#include "icinga/service.hpp"
#include "base/configobject.hpp"
#include "base/timer.hpp"
#include <fstream>

namespace icinga
{

/**
 * An Icinga perfdata writer.
 *
 * @ingroup icinga
 */
class PerfdataWriter final : public ObjectImpl<PerfdataWriter>
{
public:
	DECLARE_OBJECT(PerfdataWriter);
	DECLARE_OBJECTNAME(PerfdataWriter);

	static void StatsFunc(const Dictionary::Ptr& status, const Array::Ptr& perfdata);

	void ValidateHostFormatTemplate(const Lazy<String>& lvalue, const ValidationUtils& utils) override;
	void ValidateServiceFormatTemplate(const Lazy<String>& lvalue, const ValidationUtils& utils) override;

protected:
	void OnConfigLoaded() override;
	void Resume() override;
	void Pause() override;

private:
	void CheckResultHandler(const Checkable::Ptr& checkable, const CheckResult::Ptr& cr);
	static Value EscapeMacroMetric(const Value& value);

	Timer::Ptr m_RotationTimer;
	void RotationTimerHandler();

	std::ofstream m_ServiceOutputFile;
	std::ofstream m_HostOutputFile;
	void RotateFile(std::ofstream& output, const String& temp_path, const String& perfdata_path);
};

}

#endif /* PERFDATAWRITER_H */
