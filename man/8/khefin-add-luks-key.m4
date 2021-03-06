.TH "m4_APPNAME-add-luks-key" 8 "m4_APPDATE" "m4_APPVERSION" "m4_APPNAME-add-luks-key man page"

.SH NAME
m4_APPNAME-add-luks-key  add a LUKS key to an encrypted disk derived from a keyfile created with m4_APPNAME

.SH SYNOPSIS
.B m4_APPNAME-add-luks-key
.IR encrypted-keyfile
.IR disk
[\fIcryptsetup-options\fR]

.SH DESCRIPTION
This is a Bash script that runs \fBcryptsetup\fR(8)'s \fIluksAddKey\fR, passing in a keyfile generated with \fB`'m4_APPNAME\fR(1).
It is designed for use with the m4_APPNAME \fBmkinitcpio\fR(8) or \fBinitramfs-tools\fR(8) hooks.

\fIencrypted-keyfile\fR must have been generated by \fB`'m4_APPNAME enrol\fR.

This script must be run as root.

.SH NOTES
\fBMake an off-system backup of your LUKS header for \f(BIdisk\fB before running this command.\fR

You should also make a backup of \fIencrypted-keyfile\fR, because without this file the new keyslot on \fIdisk\fR cannot be used.

.SH BUGS
.UR https://github.com/mjec/khefin/issues
The GitHub issues page
.UE
has an up\-to\-date list of known issues. Bugs can also be reported there.

.SH SEE ALSO

.BR cryptsetup (8)
.BR m4_APPNAME (1)

Run \fBmkinitcpio -H m4_APPNAME\fR for help with the m4_APPNAME mkinitcpio hook (if installed).

See \fB`'m4_APPNAME-cryptsetup-keyscript\fR(8) for help with the m4_APPNAME initramfs-tools hook (if installed).