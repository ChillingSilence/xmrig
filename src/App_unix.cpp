/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2020 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <cstdlib>
#include <csignal>
#include <cerrno>
#include <unistd.h>


#include "App.h"
#include "base/io/log/Log.h"
#include "core/Controller.h"


bool xmrig::App::background(int &rc)
{
    if (!m_controller->isBackground()) {
        return false;
    }

    int i = fork();
    if (i < 0) {
        rc = 1;

        return true;
    }

    if (i > 0) {
        rc = 0;

        return true;
    }

    i = setsid();

    if (i < 0) {
        LOG_ERR("setsid() failed (errno = %d)", errno);
    }

    i = chdir("/");
    if (i < 0) {
        LOG_ERR("chdir() failed (errno = %d)", errno);
    }

    return false;
}
