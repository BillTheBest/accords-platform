<?php
	$metrics = "";

	require "selector.php";

	print "<form method=\"POST\" action=\"dashboard.php\">\n";

	print "<p><div class=whiteframe align=center>\n";
	print "<table width='100%'>\n";
	print "<tr><td colspan=4><div align=left><b>Service Level Agreement</b></div></th></tr>\n";

	print "<tr><td>Name</td>\n";
		print "<td><input type=text name=slaname size=64></td>\n";
		print "</tr>\n";
	print "<tr><td>Description</td>\n";
		print "<td><input type=text name=sladesc size=64></td>\n";
		print "</tr>\n";

	print "<tr><td>Account</td><td>";
	AccountSelector("slaaccount");
	print "</td>\n";

	print "<tr><td>Manifest</td><td>";
	ManifestSelector("slaservice");
	print "</td>\n";

	print "<tr><td colspan=4><div align=left><b>Service Conditions</b></div></th></tr>\n";
	print "<tr><td>Algorithm</td>";
	print "<td><select style='width: 50mm;' name=slalgo>\n";
	print "<option value=default>default</option>\n";
	print "<option value=scripted>scripted</option>\n";
	print "<option value=zone>zone</option>\n";
	print "<option value=security>security</option>\n";
	print "<option value=energy>energy</option>\n";
	print "<option value=opinion>reputation</option>\n";
	print "</select></td>\n";

	print "<tr><td>Scripted</td><td><input type=text name=slascript value='fairpack'>\n";
	print "<tr><td>Provider</td><td>\n";
	ProviderSelector("slaprovider");
	print "</td></tr>\n";

	print "<tr><td>Zone<td><select style='width: 50mm;' name=slazone>\n";
	print "<option value=any>any</option>\n";
	print "<option value='europe'>europe</option>\n";
	print "<option value='west-europe'>west europe</option>\n";
	print "<option value='east-europe'>east europe</option>\n";
	print "<option value='asia'>asia</option>\n";
	print "<option value='north-asia'>north asia</option>\n";
	print "<option value='south-asia'>south asia</option>\n";
	print "<option value='east-asia'>east asia</option>\n";
	print "<option value='west-asia'>west asia</option>\n";
	print "<option value='america'>america</option>\n";
	print "<option value='us-east'>united states east</option>\n";
	print "<option value='us-west'>united states west</option>\n";
	print "<option value='north-america'>north america</option>\n";
	print "<option value='south-america'>south america</option>\n";
	print "<option value='africa'>africa</option>\n";
	print "<option value='north-africa'>north africa</option>\n";
	print "<option value='south-africa'>south africa</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Rating<td><select style='width: 50mm;' name=slarating>\n";
	print "<option value=any>any</option>\n";
	for ( $i=1; $i <= 10; $i += 1 )
	{
		print "<option value='".$i."'>".$i."</option>\n";
	}
	print "</select></td></tr>\n";

	print "<tr><td>Security<td><select style='width: 50mm;' name=slasecurity>\n";
	print "<option value=any>any</option>\n";
	print "<option value=trusted>trusted</option>\n";
	print "<option value=untrusted>untrusted</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Energy<td><select style='width: 50mm;' name=slaenergy>\n";
	print "<option value=any>any</option>\n";
	print "<option value=high>high</option>\n";
	print "<option value=normal>normal</option>\n";
	print "<option value=low>low</option>\n";
	print "</select></td></tr>\n";

	/* --------------------- */
	/* Load Balancer Options */
	/* --------------------- */
	print "<tr><td colspan=4><div align=left><b>Scalability Conditions</b></div></th></tr>\n";
	print "<tr><td>Floor<td><input type=text name=ejf value=''></tr>";
	print "<tr><td>Ceiling<td><input type=text name=ejc value=''></tr>";
	print "<tr><td>Strategy<td><select style='width: 50mm;' name=ejs>\n";
	print "<option value=301>301 Moved Permenant</option>\n";
	print "<option value=302>302 Moved Temporary</option>\n";
	print "<option value=303>303 Moved Temporary GET</option>\n";
	print "<option value=307>307 Moved Temporary POST</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td colspan=4><div align=left><b>Service Guarantees</b></div></th></tr>\n";
	
	print "<tr><td>Scope</td><td ><input type=text name=gs1 value='default'></tr>\n";
	print "<tr><td>Property</td><td >\n";
	$metrics = MetricSelector("gp1",$metrics);
	print "</td></tr>\n";

	print "<tr><td>Must not be</td><td >\n";
	print "<select style='width: 50mm;' name=gc1>\n";
	print "<option value=eq>equal</option>\n";
	print "<option value=ne>not equal</option>\n";
	print "<option value=gr>greater</option>\n";
	print "<option value=le>not greater</option>\n";
	print "<option value=ls>less</option>\n";
	print "<option value=ge>not less</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Value</td><td><input type=text name=gv1 size=64></td>\n";

	print "<tr><td>Business Value</td><td >\n";
	print "<select style='width: 50mm;' name=gb1>\n";
	print "<option value=none>none</option>\n";
	print "<option value=penalty>penalty</option>\n";
	print "<option value=reward>reward</option>\n";
	print "<option value=both>both</option>\n";
	print "</select></td></tr>\n";
	print "<tr><td>Expression</td><td><input type=text name=gx1 size=64></td>\n";
	print "<tr><td colspan=2><hr></td></tr>\n";

	print "<tr><td>Scope</td><td ><input type=text name=gs2 value='default'></tr>\n";
	print "<tr><td>Property</td><td >\n";
	$metrics = MetricSelector("gp2",$metrics);
	print "</td></tr>\n";

	print "<tr><td>Must not be</td><td >\n";
	print "<select style='width: 50mm;' name=gc2>\n";
	print "<option value=eq>equal</option>\n";
	print "<option value=ne>not equal</option>\n";
	print "<option value=gr>greater</option>\n";
	print "<option value=le>not greater</option>\n";
	print "<option value=ls>less</option>\n";
	print "<option value=ge>not less</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Value</td><td><input type=text name=gv2 size=64></td>\n";

	print "<tr><td>Business Value</td><td >\n";
	print "<select style='width: 50mm;' name=gb2>\n";
	print "<option value=none>none</option>\n";
	print "<option value=penalty>penalty</option>\n";
	print "<option value=reward>reward</option>\n";
	print "<option value=both>both</option>\n";
	print "</select></td></tr>\n";
	print "<tr><td>Expression</td><td><input type=text name=gx2 size=64></td>\n";
	print "<tr><td colspan=2><hr></td></tr>\n";

	print "<tr><td>Scope</td><td ><input type=text name=gs3 value='default'></tr>\n";
	print "<tr><td>Property</td><td >\n";
	$metrics = MetricSelector("gp3",$metrics);
	print "</td></tr>\n";

	print "<tr><td>Must not be</td><td >\n";
	print "<select style='width: 50mm;' name=gc3>\n";
	print "<option value=eq>equal</option>\n";
	print "<option value=ne>not equal</option>\n";
	print "<option value=gr>greater</option>\n";
	print "<option value=le>not greater</option>\n";
	print "<option value=ls>less</option>\n";
	print "<option value=ge>not less</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Value</td><td><input type=text name=gv3 size=64></td>\n";

	print "<tr><td>Business Value</td><td >\n";
	print "<select style='width: 50mm;' name=gb3>\n";
	print "<option value=none>none</option>\n";
	print "<option value=penalty>penalty</option>\n";
	print "<option value=reward>reward</option>\n";
	print "<option value=both>both</option>\n";
	print "</select></td></tr>\n";
	print "<tr><td>Expression</td><td><input type=text name=gx3 size=64></td>\n";
	print "<tr><td colspan=2><hr></td></tr>\n";

	print "<tr><td>Scope</td><td ><input type=text name=gs4 value='default'></tr>\n";
	print "<tr><td>Property</td><td >\n";
	$metrics = MetricSelector("gp4",$metrics);
	print "</></td></tr>\n";

	print "<tr><td>Must not be</td><td >\n";
	print "<select style='width: 50mm;' name=gc4>\n";
	print "<option value=eq>equal</option>\n";
	print "<option value=ne>not equal</option>\n";
	print "<option value=gr>greater</option>\n";
	print "<option value=le>not greater</option>\n";
	print "<option value=ls>less</option>\n";
	print "<option value=ge>not less</option>\n";
	print "</select></td></tr>\n";

	print "<tr><td>Value</td><td><input type=text name=gv4 size=64></td>\n";

	print "<tr><td>Business Value</td><td >\n";
	print "<select style='width: 50mm;' name=gb4>\n";
	print "<option value=none>none</option>\n";
	print "<option value=penalty>penalty</option>\n";
	print "<option value=reward>reward</option>\n";
	print "<option value=both>both</option>\n";
	print "</select></td></tr>\n";
	print "<tr><td>Expression</td><td><input type=text name=gx4 size=64></td>\n";
	print "<tr><td colspan=2><hr></td></tr>\n";

	print "<tr><td>Submit<td><div align=center><input class='action' type=submit name=action value='generate sla then parse'></div>\n";

	print "</table></div>\n";
	print "</form>\n";
?>

