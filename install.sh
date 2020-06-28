#!/bin/bash

#   This script is part of Ahora © Plateform
#   
#   \details        System :                Vera GUI
#                   Component Name :        vera
#                   Status :                Version 1.0.0 Release 1
#                   Language :              C++
# 
#                   Platform Dependencies:  GNU/Linux, Windows, MacOS
# 
#   \copyright      GPLv3+ : GNU GPL version 3 or later
#                   Licencied Material - Property of IMT ATLANTIQUE
#                   © Copyright - UHA - ENSISA 2020
# 
#   \author         Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
# 
#   \bug            No known bug to date
#   \date           21th May 2020
#
#   This text plain is developed in the hope that it will be useful
#   but WITHOUT ANY WARRANTY ; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

#   Default flags
ERROR="[\033[31m!\033[0m]"
DEBUG="[\033[33m#\033[0m]"
OK="[\033[32mo\033[0m]"

#   By default PREROGATIVE is set to sudo for normal users
if [[ $USER = root ]]; then
    export PREROGATIVE=
else
    export PREROGATIVE=sudo
fi

#   Default commands
ECHO="echo -e"

#   Check GNU/Linux distribtion function
function checkDistrib() {
    DISTRIB=$(cat /etc/os-release | grep "NAME" | head -n 1 | cut -d'"' -f2 | cut -d' ' -f1)

    if [[ "$DISTRIB" = "CentOS" ]]; then
        # Define appropriate download manager for CentOS Distribution
        DOWN_MANAG="yum"
        PKG_MANAG="rpm"
    elif [[ "$DISTRIB" = "Debian" ]] || [[ "$DISTRIB" = "Kali" ]]; then
        # Define appropriate download manager for Debian Like Distribution
        DOWN_MANAG="apt-get"
        PKG_MANAG="dpkg-query"
    elif [[ "$DISTRIB" = "Mageia" ]]; then
        # Define appropriate download manager for Mageia Distribution
        DOWN_MANAG="urpmi"
        PKG_MANAG="rpm"
    elif [[ "$DISTRIB" = "Arch" ]]; then
        # Define appropriate download manager for Arch Linux Distribution
        DOWN_MANAG="pacman"
        PKG_MANAG="pacman"
    else
        return 1
    fi
}

#   Install missing package functions
function installMissingPKG() {
    if [ -z "$1" ]; then
        ${ECHO} "${ERROR} \$PKG is empty"
    else
        COMMAND=$(${PKG_MANAG} -W -f='${Status}\n' $1 | cut -d' ' -f1)
        if [[ "$COMMAND" = "install" ]]; then
            ${ECHO} "${OK} $1 is installed"
            sleep 1
        else
            ${ECHO} "${ERROR} $1 is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of $1 ..."
            ${PREROGATIVE} ${DOWN_MANAG} install -y $1 > /dev/null
            sleep 2
            ${ECHO} "${OK} $1 has been installed"
        fi
    fi
}

function installMissingPKGBUILD() {
    if [ -z "$1" ]; then
        echo "\$PKG is empty"
    else
        COMMAND=$(${PKG_MANAG} -Qi $1)
        if [ -z "$COMMAND" ]; then
            ${ECHO} "${ERROR} $1 is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of $1 ..."
            ${PREROGATIVE} ${DOWN_MANAG} -Syy $1 > /dev/null
            sleep 2
            ${ECHO} "${OK} $1 has been installed"
        else
            ${ECHO} "${OK} $1 is installed"
            sleep 1
        fi
    fi
}

function installMissingRPM() {
    if [ -z "$1" ]; then
        echo "\$PKG is empty"
    else
        export NUX=nux-dextop-release
        FIREWALL=$(${PKG_MANAG} -qa ${NUX})

        if [ -z "$FIREWALL" ]; then
            ${ECHO} "${ERROR} ${NUX} is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of ${NUX} ..."

            #   Load missing repositories
            ${PREROGATIVE} ${PKG_MANAG} --import http://li.nux.ro/download/nux/RPM-GPG-KEY-nux.ro
            ${PREROGATIVE} ${PKG_MANAG} -Uvh http://li.nux.ro/download/nux/dextop/el7/x86_64/nux-dextop-release-0-1.el7.nux.noarch.rpm > /dev/null

            #   Uploading repositories
            ${PREROGATIVE} ${DOWN_MANAG} update -y > /dev/null
        fi

        COMMAND=$(${PKG_MANAG} -qa $1)
        if [ -z "$COMMAND" ]; then
            ${ECHO} "${ERROR} $1 is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of $1 ..."
            ${PREROGATIVE} ${DOWN_MANAG} install -y $1 > /dev/null
            sleep 2
            ${ECHO} "${OK} $1 has been installed"
        else
            ${ECHO} "${OK} $1 is installed"
            sleep 1
        fi
    fi
}

#   String arrays of packages
declare -a PKGS_CENTOS=(
                "build-essential"
                "cmake3"
                "doxygen"
                "gcc"
                "gcc-c++"
                "git"
                "make"
                "qtcreator"
)

declare -a PKGS_DEBIAN=(
                "build-essential"
                "cmake"
                "doxygen"
                "gcc"
                "g++"
                "git"
                "make"
                "qtbase5-dev" 
                "qtdeclarative5-dev"
                "qtmultimedia5-dev"
                "qt3d5-dev"
)

declare -a PKGS_KALI=(
                "build-essential"
                "cmake"
                "doxygen"
                "gcc"
                "g++"
                "git"
                "make"
                "qtbase5-dev" 
                "qtdeclarative5-dev"
                "qtmultimedia5-dev"
                "qt3d5-dev"
)

declare -a PKGS_MAGEIA=(
                "cmake"
                "gcc"
                "gcc-c++"
                "git"
                "make"
)

declare -a PKGS_ARCH=(
                "cmake"
                "gcc"
                "make"
                "git"
                "qt5-3d"
                "qt5-base"
                "qt5-charts"
                "qt5-connectivity"
                "qt5-datavis3d"
                "qt5-declarative"
                "qt5-doc"
                "qt5-examples"
                "qt5-gamepad"
                "qt5-graphicaleffects"
                "qt5-imageformats"
                "qt5-location"
                "qt5-lottie"
                "qt5-multimedia"
                "qt5-networkauth"
                "qt5-purchasing"
                "qt5-quick3d"
                "qt5-quickcontrols"
                "qt5-quickcontrols2"
                "qt5-quicktimeline"
                "qt5-remoteobjects"
                "qt5-script"
                "qt5-scxml"
                "qt5-sensors"
                "qt5-serialbus"
                "qt5-serialport"
                "qt5-speech"
                "qt5-svg"
                "qt5-tools"
                "qt5-translations"
                "qt5-virtualkeyboard"
                "qt5-wayland"
                "qt5-webchannel"
                "qt5-webengine"
                "qt5-webglplugin"
                "qt5-websockets"
                "qt5-webview"
                "qt5-x11extras"
                "qt5-xmlpatterns"
                "doxygen"
                "graphviz"
                "dot2tex"
                "python-graphviz"
                "python-pydot"
)

#   Display Welcome message
${ECHO} "Vera © Plateform"
${ECHO} "GPLv3+ : GNU GPL version 3 or later"
${ECHO} "Licencied Material - Property of IMT ATLANTIQUE"
${ECHO} "© Copyright - UHA - ENSISA 2020\n"
${ECHO} "Starting the configuration of your GNU/Linux Operating System"
${ECHO} ""

#   Execute Check GNU/Linux distribtion function
checkDistrib

if [[ "$DISTRIB" = "CentOS" ]]; then
    #   Loop list of packages
    for PKG in "${PKGS_CENTOS[@]}"; do
        # Execute Install missing package function
        installMissingRPM ${PKG}
    done
elif [[ "$DISTRIB" = "Debian" ]]; then
    #   Loop list of pakages
    for PKG in "${PKGS_DEBIAN[@]}"; do
        #   Execute Install missing package function
        installMissingPKG ${PKG}
    done
elif [[ "$DISTRIB" = "Kali" ]]; then
    #   Loop list of pakages
    for PKG in "${PKGS_KALI[@]}"; do
        #   Execute Install missing package function
        installMissingPKG ${PKG}
    done
elif [[ "$DISTRIB" = "Arch" ]]; then
    #   Loop list of pakages
    for PKG in "${PKGS_ARCH[@]}"; do
        #   Execute Install missing package function
        installMissingPKGBUILD ${PKG}
    done
fi

${ECHO} ""
${ECHO} "Configuration done"