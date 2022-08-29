#!/bin/bash

script_file=TS-M1N3.pkgproj

app_version=$(cut -f 2 -d '=' <<< "$(grep 'CMAKE_PROJECT_VERSION:STATIC' ../../build/CMakeCache.txt)")
echo "Setting app version: $app_version..."
sed -i '' "s/##APPVERSION##/${app_version}/g" $script_file
sed -i '' "s/##APPVERSION##/${app_version}/g" Intro.txt

echo "Copying License..."
cp ../../LICENSE.txt LICENSE.txt

# build installer
echo Building...
/usr/local/bin/packagesbuild $script_file

# reset version number
sed -i '' "s/${app_version}/##APPVERSION##/g" $script_file
sed -i '' "s/${app_version}/##APPVERSION##/g" Intro.txt

# clean up license file
rm LICENSE.txt

# sign the installer package
echo "Signing installer package..."
TEAM_ID=$(more ~/Developer/mac_id)
pkg_dir=TS-M1N3_Installer_Packaged
rm -Rf $pkg_dir
mkdir $pkg_dir
productsign -s "$TEAM_ID" ../../build/TS-M1N3.pkg $pkg_dir/TS-M1N3-signed.pkg

echo "Notarizing installer package..."
INSTALLER_PASS=$(more ~/Developer/mac_installer_pass)
npx notarize-cli --file $pkg_dir/TS-M1N3-signed.pkg --bundle-id com.GuitarML.TS-M1N3 --asc-provider "$TEAM_ID" --username smartguitarml@gmail.com --password "$INSTALLER_PASS"

echo "Building disk image..."
vol_name=Install_TS-M1N3-$app_version
hdiutil create "$vol_name.dmg" -fs HFS+ -srcfolder $pkg_dir -format UDZO -volname "$vol_name"
