/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#include "BTTrackerGroup.h"
#include "BTTrackerConnection.h"
#include "folder/FolderGroup.h"
#include "util/log.h"

namespace librevault {

BTTrackerGroup::BTTrackerGroup(BTTrackerProvider* provider, FolderGroup* fgroup) : provider_(provider),
	ih_(btcompat::getInfoHash(fgroup->folderid())),
	folderid_(fgroup->folderid()) {}

void BTTrackerGroup::setEnabled(bool enabled) {
	if(enabled) {
		for(auto tracker : Config::get()->global_get("bttracker_trackers")) {
			QUrl tracker_address = QString::fromStdString(tracker.asString());
			connections_[tracker_address] = std::make_unique<BTTrackerConnection>(tracker_address, this, provider_);
			LOGD("Added BitTorrent tracker: " << tracker_address.toString());
		}
	}else{
		connections_.clear();
	}
}

} /* namespace librevault */
