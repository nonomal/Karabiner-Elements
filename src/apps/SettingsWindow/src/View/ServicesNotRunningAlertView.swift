import ServiceManagement
import SwiftUI

struct ServicesNotRunningAlertView: View {
  var body: some View {
    ZStack(alignment: .topLeading) {
      VStack(alignment: .center, spacing: 20.0) {
        Label(
          "The background services are not running. Please enable them.",
          systemImage: "exclamationmark.triangle"
        )
        .font(.system(size: 24))

        GroupBox {
          VStack(alignment: .center, spacing: 20.0) {
            VStack(alignment: .center, spacing: 0.0) {
              Text("To use Karabiner-Elements, you need to run the background services.")
              Text(
                "Please enable the following items from System Settings > General > Login Items."
              )
            }

            VStack(alignment: .leading, spacing: 0.0) {
              Label(
                "Karabiner-Elements Non-Privileged Agents",
                systemImage:
                  ServicesMonitor.shared.agentRunning ? "checkmark.circle" : "circle")
              Label(
                "Karabiner-Elements Privileged Daemons",
                systemImage:
                  ServicesMonitor.shared.daemonRunning ? "checkmark.circle" : "circle")
            }

            Button(
              action: {
                SMAppService.openSystemSettingsLoginItems()
              },
              label: {
                Label(
                  "Open System Settings > General > Login Items",
                  systemImage: "arrow.forward.circle.fill")
              })

            Label(
              "If these are already enabled, the settings might not be properly reflected on the macOS side. Please disable them once and then enable them again.",
              systemImage: "lightbulb"
            )
            .padding()
            .foregroundColor(Color.warningForeground)
            .background(Color.warningBackground)

            Image(decorative: "login-items")
              .resizable()
              .aspectRatio(contentMode: .fit)
              //.frame(height: 250)
              .border(Color.gray, width: 1)

          }
          .padding()
        }
      }
      .padding()
      .frame(width: 850)

      SheetCloseButton {
        ContentViewStates.shared.showServicesNotRunningAlert = false
      }
    }
  }
}

struct ServicesNotRunningAlertView_Previews: PreviewProvider {
  static var previews: some View {
    Group {
      ServicesNotRunningAlertView()
        .previewLayout(.sizeThatFits)
    }
  }
}