using UnityEngine;

namespace Code.Data
{
    [CreateAssetMenu(fileName = "MainCamera.asset", menuName = "Data/Camera Reference", order = 0)]
    public class CameraReference : ScriptableObject
    {
        public Camera value;
    }
}