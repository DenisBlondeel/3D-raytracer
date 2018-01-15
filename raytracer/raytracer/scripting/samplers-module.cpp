#ifndef EXCLUDE_SCRIPTING

#include "scripting/samplers-module.h"
#include "samplers/samplers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct SamplerLibrary
    {
        Sampler single() const
        {
            return samplers::single();
        }
		Sampler random(int points) const
		{
			return samplers::random(points);
		}
		Sampler stratified(int N, int M) const
		{
			return samplers::stratified(N, M);
		}
		Sampler jittered(int N, int M) const
		{
			return samplers::jittered(N, M);
		}
		Sampler halfjittered(int N, int M) const
		{
			return samplers::halfjittered(N, M);
		}
		Sampler nrooks(int N) const
		{
			return samplers::nrooks(N);
		}
		Sampler multijittered(int N) const
		{
			return samplers::multijittered(N);
		}
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Sampler>(*module, "Sampler");

    auto sampler_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(sampler_library), "Samplers");

#   define BIND(NAME)  module->add(fun(&SamplerLibrary::NAME), #NAME)
    BIND(single);
	BIND(random);
	BIND(stratified);
	BIND(jittered);
	BIND(halfjittered);
	BIND(nrooks);
	BIND(multijittered);
#   undef BIND

    return module;
}

#endif
