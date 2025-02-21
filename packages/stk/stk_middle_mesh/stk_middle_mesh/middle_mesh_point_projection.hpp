#ifndef STK_MIDDLE_MESH_POINT_PROJECTION
#define STK_MIDDLE_MESH_POINT_PROJECTION

#include "nonconformal_abstract.hpp"
#include "predicates/point_classifier_normal_wrapper.hpp"
#include "mesh_relational_data.hpp"
#include "gauss_newton.hpp"

namespace stk {
namespace middle_mesh {
namespace nonconformal4 {
namespace impl {


// Given a middle mesh and a set of xi coordinates on the middle mesh
// elements, compute the xi coordinates of their projections onto
// either mesh1 or mesh2
class MiddleMeshPointProjection
{
  public:
    MiddleMeshPointProjection(std::shared_ptr<mesh::Mesh> mesh1,
                              std::shared_ptr<mesh::Mesh> mesh2,
                              std::shared_ptr<mesh::Mesh> meshIn,
                              std::shared_ptr<MeshRelationalData> relationalData,
                              std::shared_ptr<predicates::impl::PointClassifierNormalWrapper> classifier) :
      m_mesh1(mesh1),
      m_mesh2(mesh2),
      m_meshIn(meshIn),
      m_relationalData(relationalData),
      m_classifier(classifier),
      m_gaussNewton(3, 2, 1e-13, 100),
      m_xi0(2)
    {}

    mesh::FieldPtr<utils::Point> projection_onto_mesh1(std::shared_ptr<XiCoordinates> xiCoords);

    mesh::FieldPtr<utils::Point> projection_onto_mesh2(std::shared_ptr<XiCoordinates> xiCoords);

  private:
    utils::Point compute_nearest_point_on_quad(mesh::MeshEntityPtr el, const utils::Point& ptXyz, const utils::Point& ptXiGuess);

    std::shared_ptr<mesh::Mesh> m_mesh1;
    std::shared_ptr<mesh::Mesh> m_mesh2;
    std::shared_ptr<mesh::Mesh> m_meshIn;
    std::shared_ptr<MeshRelationalData> m_relationalData;
    std::shared_ptr<predicates::impl::PointClassifierNormalWrapper> m_classifier;
    utils::impl::GaussNewton m_gaussNewton;
    std::vector<double> m_xi0;
};

} // namespace 
} // namespace 
} // namespace 
} // namespace 

#endif