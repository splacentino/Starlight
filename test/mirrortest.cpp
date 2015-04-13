#include "test/catch.hpp"
#include <iostream>
#include "model/starlightexception.hpp"
#include "model/geometry/utilities.hpp"
#include "model/geometry/line.hpp"
#include "model/ray.hpp"
#include "model/mirror.hpp"
#include "model/point.hpp"

TEST_CASE("Construction")
{
    REQUIRE_NOTHROW(Mirror(Point(2., 2.), 2, 5, 1., Point(1., 1.), Point(3., 3.), 0., 2.));
    REQUIRE_THROWS_AS(Mirror(Point(2., 2.), -1, 5, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(2., 2.), 1, 0, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(4., 2.), 1, 1, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(2., 4.), 1, 1, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(2., 0.), 1, 1, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(0., 2.), 1, 1, 1., Point(1., 1.), Point(3., 3.), 0., 2.),
                      StarlightException);
    REQUIRE_THROWS_AS(Mirror(Point(2., 2.), 1, 1, 2., Point(1., 1.), Point(3., 3.), 2.1, 2.),
                      StarlightException);
}

TEST_CASE("Miroir : Accesseurs")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    REQUIRE(mirroir.getPivot() == Point(4.6350324277, 6.0423035858));
    REQUIRE(mirroir.getXPad() == 50);
    REQUIRE(mirroir.getLength() == 80);
    REQUIRE(utilities::equals(mirroir.getAngle(), 5.1882683952));
    REQUIRE(mirroir.getMinPivot() == Point(1., 1.));
    REQUIRE(mirroir.getMaxPivot() == Point(221., 2221.));
    REQUIRE(utilities::equals(mirroir.getMinAngle(), utilities::PI));
    REQUIRE(utilities::equals(mirroir.getMaxAngle(), utilities::PI * 2));
}

TEST_CASE("Mirroir : setPivot")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    REQUIRE(mirroir.setPivot(Point(2., 2.)));
    REQUIRE_FALSE(mirroir.setPivot(Point(0., 2.)));
    REQUIRE_FALSE(mirroir.setPivot(Point(1., 2221.1)));
}

TEST_CASE("Mirroir : setAngle")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    REQUIRE(mirroir.setAngle(5.));
    REQUIRE(mirroir.setAngle(utilities::PI));
    REQUIRE(mirroir.setAngle(utilities::PI * 2));
    REQUIRE_FALSE(mirroir.setAngle(1.));
}

TEST_CASE("Mirroir : CheckAngleRange")
{
    SECTION("Max = Min = 0")
    {
        Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};

        REQUIRE(mirroir.checkAngleRange(1999.));
        REQUIRE(mirroir.checkAngleRange(-999.));
    }

    SECTION("!(Max = Min = 0)")
    {
        Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 4.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 5.};

        REQUIRE(mirroir.checkAngleRange(4.));
        REQUIRE(mirroir.checkAngleRange(2.));
        REQUIRE_FALSE(mirroir.checkAngleRange(-1.));
        REQUIRE_FALSE(mirroir.checkAngleRange(6.));
    }

}

TEST_CASE("Mirroir : pivotRange")
{
    SECTION("xmin = xmax = ymin = ymax = 0")
    {
        Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 4.1882683952,
                       Point{0.,0.}, Point{0., 0.}, 0., 5.};

        REQUIRE(mirroir.checkPivotRange(Point(22., -33)));
        REQUIRE(mirroir.checkPivotRange(Point(-22.2223, -33)));
    }

    SECTION("xmin = xmax = 0")
    {
        Mirror mirroir{Point{4., 6.}, 50, 80, 4.1882683952,
                       Point{0.,-220.}, Point{0., 31.}, 0., 5.};

        REQUIRE(mirroir.checkPivotRange(Point(22., 30)));
        REQUIRE(mirroir.checkPivotRange(Point(-222., 30)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(-22.2223, 33)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(-22.2223, -221)));

    }

    SECTION("ymin = ymax = 0")
    {
        Mirror mirroir{Point{4., 6.}, 50, 80, 4.1882683952,
                       Point{-220.,0.}, Point{31., 0.}, 0., 5.};

        REQUIRE(mirroir.checkPivotRange(Point(-22., 2.230)));
        REQUIRE(mirroir.checkPivotRange(Point(-122., -3330)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(32.2223, 33)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(-222.2223, -221)));
    }

    SECTION("Quelconque")
    {
        Mirror mirroir{Point{4., 55.}, 50, 80, 4.1882683952,
                       Point{-220.,40.}, Point{31., 90.}, 0., 5.};

        REQUIRE(mirroir.checkPivotRange(Point(-22., 50)));
        REQUIRE(mirroir.checkPivotRange(Point(-122., 89)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(-332.2223, 33)));
        REQUIRE_FALSE(mirroir.checkPivotRange(Point(-222.2223, -221)));
    }
}

TEST_CASE("Mirroir : reactToRay")
{
    Mirror mirroir{Point{4., 55.}, 50, 80, 4.1882683952,
                   Point{-220.,40.}, Point{31., 90.}, 0., 5.};

    REQUIRE_NOTHROW(mirroir.reactToRay(Ray(Point(2., 2.), 3., 400)));
}

TEST_CASE("Mirroir : opérateurs")
{
    Mirror mirroir{Point{4., 55.}, 50, 80, 4.1882683952,
                   Point{-220.,40.}, Point{31., 90.}, 0., 5.};

    Mirror mirr{Point{4., 55.}, 50, 80, 4.1882683952,
                Point{-220.,40.}, Point{31., 90.}, 0., 5.};

    REQUIRE(mirroir == mirr);
    REQUIRE_FALSE(mirroir != mirr);
}

TEST_CASE("Reflexion de mirroir angle quelconque")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    Ray ray{Point{3.8690993528, 1.9060097494}, 1.0492334171, 500};

    Point point{5.3967177826, 4.5644066284};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), -0.0977844768));
    REQUIRE(utilities::equals(newRay.getIndepTerm(), 5.0921218532));
}

TEST_CASE("Reflexion de mirroir angle quelconque : 2")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, (5.1882683952 - (2 * utilities::PI)),
                Point{1.,1.}, Point{221., 2221.}, 0., 0.};

    Ray ray{Point{3.8690993528, 1.9060097494}, 1.0492334171, 500};

    Point point{5.3967177826, 4.5644066284};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), -0.0977844768));
    REQUIRE(utilities::equals(newRay.getIndepTerm(), 5.0921218532));
}


TEST_CASE("Reflexion de mirroir angle quelconque deux")
{
    Mirror mirroir{Point{1.7607403534, 6.592301552}, 50, 80, 5.6513040756,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    Ray ray{Point{1.499676861, 2.0584973355}, 0.5303315945, 500};

    Point point{5.0835944758, 4.1599723344};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), 4.403644668));
    REQUIRE(utilities::equals(newRay.getIndepTerm(), -18.2263713732));
}

TEST_CASE("Reflexion sur mirroir vertical et angle de tir 0°")
{
    Mirror mirroir{Point{6.7091129602, 5.7891302282}, 50, 80, (3. * utilities::PI) / 2.,
                Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    Ray ray{Point{0.687119753, 2.0988911382}, 0., 500};

    Point point{6.7091129602, 2.0988911382};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), 0.));
    REQUIRE(utilities::equals(newRay.getIndepTerm(),  2.0988911382));
}

TEST_CASE("Reflexion sur mirroir vertical et angle de tir 0° avec"
          "angle en surplus de 2PI")
{
    Mirror mirroir{Point{6.7091129602, 5.7891302282}, 50, 80, -(utilities::PI / 2.),
                Point{1.,1.}, Point{221., 2221.}, -utilities::PI * 2, utilities::PI * 2};

    Ray ray{Point{0.687119753, 2.0988911382}, 0., 500};

    Point point{6.7091129602, 2.0988911382};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), 0.));
    REQUIRE(utilities::equals(newRay.getIndepTerm(),  2.0988911382));
}

TEST_CASE("Reflexion sur mirroir horizontale et perpendiculaire au tir")
{
    Mirror mirroir{Point{3.1027244297, 6.9894297822}, 50, 80, 0.,
                   Point{1.,1.}, Point{221., 2221.}, 0., utilities::PI * 2};

    Ray ray{Point{8.0884039814, 1.1190305352}, utilities::PI_2, 500};

    Point point{8.0884039814, 6.9894297822};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(newRay.isVertical());
    REQUIRE(utilities::equals(newRay.getXValue(),  8.0884039814));
}

TEST_CASE("Reflexion de mirroir angle quelconque + 2PI")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    Ray ray{Point{3.8690993528, 1.9060097494}, 1.0492334171 + (2* utilities::PI), 500};

    Point point{5.3967177826, 4.5644066284};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), -0.0977844768));
    REQUIRE(utilities::equals(newRay.getIndepTerm(), 5.0921218532));
}

TEST_CASE("Reflexion de mirroir angle quelconque négatif")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 50, 80, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

    Ray ray{Point{3.8690993528, 1.9060097494}, -((utilities::PI * 2) - 1.0492334171), 500};

    Point point{5.3967177826, 4.5644066284};
    double mirror = utilities::absoluteAngle(mirroir.getAngle());
    if (utilities::equals(mirror, 0.))
        mirror = 0.;

    double source = utilities::absoluteAngle(std::atan(ray.getSlope()));
    if (utilities::equals(source, 0.))
        source = 0.;

    double alpha = (utilities::PI - mirror - source);
    if (utilities::equals(alpha, 0.))
        alpha = 0.;

    Ray newRay(point, (source + alpha + alpha), ray.getWaveLength());

    REQUIRE(utilities::equals(newRay.getSlope(), -0.0977844768));
    REQUIRE(utilities::equals(newRay.getIndepTerm(), 5.0921218532));
}

TEST_CASE("includeRay")
{

    SECTION("Droite quelconque : pas d'intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{0.9131453839, 2.4382207854}, -0.5657014687, 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection == 0);
    }

    SECTION("Droite quelconque : intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{0.9131453839, 2.4382207854}, 0.2478814126, 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection != 0);
        REQUIRE(*intersection == Point(7.036920316, 3.9880650583));
        delete intersection;
    }
    SECTION("Droite horizontale : pas intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{0.8787051129, 11.6682134228}, 0., 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection == 0);
    }

    SECTION("Droite horizontale : intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{0.8787051129, 8.6682134228}, 0., 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection != 0);
        REQUIRE(*intersection == Point(4.6248438514, 8.6682134228));
        delete intersection;

    }

    SECTION("Droite verticale : pas d'intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{2.5662783936, 12.5981007408}, -utilities::PI_2, 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection == 0);

    }

    SECTION("Droite verticale : d'intersection")
    {
        Mirror mirroir{Point{6., 6.}, 5, 8, 5.1882683952,
                       Point{1.,1.}, Point{221., 2221.}, 0., 0.};
        Ray ray{Point{4.5662783936, 12.5981007408}, -utilities::PI_2, 500};

        Point * intersection = mirroir.includeRay(ray);
        REQUIRE(intersection != 0);
        REQUIRE(*intersection == Point(4.5662783936, 8.7818478932));
        delete intersection;
    }
}

TEST_CASE("Mirroir est un rayon")
{
    Mirror mirroir{Point{4.6350324277, 6.0423035858}, 5, 8, 5.1882683952,
                   Point{1.,1.}, Point{221., 2221.}, utilities::PI, utilities::PI * 2};

}
