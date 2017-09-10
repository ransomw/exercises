#! /bin/sh

EXPECTED_VERSION="3.6.1"
ACTUAL_VERSION="$(python --version | sed 's/Python //')"
if [ "$ACTUAL_VERSION" != "$EXPECTED_VERSION" ]
then
    echo "expecting python $EXPECTED_VERSION, " \
         "found $ACTUAL_VERSION" 1>&2
    exit 1
fi
echo "..ok"

# PIP_FLAGS=" -q"
echo "updating python packages"
PACKAGES_TO_UNINSTALL=$(pip freeze | grep -v -f requirements.txt -)
if [ "$PACKAGES_TO_UNINSTALL" != '' ]
then
    echo "$PACKAGES_TO_UNINSTALL" | \
        xargs pip uninstall -y $PIP_FLAGS
    if [ $? != 0 ]
    then
        echo "pip uninstall failed" 1>&2
        exit 2
    fi
fi
pip install -r requirements.txt $PIP_FLAGS
if [ $? != 0 ]
then
    echo "pip install failed" 1>&2
    exit 2
fi
