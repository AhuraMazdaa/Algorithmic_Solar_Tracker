# Algorithmic_Solar_Tracker
This library was used on arduino platform to calculate the azimuth and elevation of the sun.
It needs the lat long as inputs and the local time in terms of Apparent Solar Time.

φ = Local Latitude of the observer (positive for North, negative for South).
δ = Solar Declination Angle (the angle of the Sun relative to the Earth's equator; ranges from -23.45° to +23.45°).
H (or ω) = Hour Angle (the angular distance of the Sun from solar noon; calculated as 15° × (Solar Time - 12)).

First we calculate the elevation by using formula (derived from spherical geometry):
sin (α)= sin(δ) * sin (φ) + cos(δ) * cos(φ) * cos(H) OR
α =arcsin( sin(δ)*sin (φ) + cos(δ)*cos(φ)*cos(H) )

then we plug α into the formula for azimuth
azimuth = arccos((sin(δ) - (sin(α) * sin(ϕ))) / (cos(α) * cos(ϕ)))
