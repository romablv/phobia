#include "ntc.h"
#include "phobia/libm.h"

float ntc_temperature(ntc_t *ntc, float u)
{
	float			r_ntc, log, temp;

	r_ntc = ntc->r_balance * u / (1.f - u);

	log = m_logf(r_ntc / ntc->r_ntc_0);
	temp = 1.f / (1.f / (ntc->ta_0 + 273.f) + log / ntc->betta) - 273.f;

	return temp;
}

float ats_temperature(ntc_t *ntc, float u)
{
	return (ntc->ta_0 - u) * ntc->betta;
}

